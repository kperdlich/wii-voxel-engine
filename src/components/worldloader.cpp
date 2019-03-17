#include "worldloader.h"
#include "../textures/Label.h"
#include "../utils/Filesystem.h"
#include "../net/NetworkManager.h"
#include "../net/packet/PacketHandshake.h"
#include "../event/eventmanager.h"
#include "../event/event.h"
#include "../scenes/Basic3DScene.h"
#include "../Engine.h"

WorldLoader::WorldLoader(const char* name, Sprite* sprite) : UiTextureElement(0, 0, name, sprite),
    m_state(EWorldLoaderState::CHECK_WORLD_CASH), m_nextState(EWorldLoaderState::CHECK_WORLD_CASH)
{
    m_pStateLabel = Label::Create("",
                                  Engine::Get().GetFontHandler().GetNativFontByID(DEFAULT_MINECRAFT_FONT_ID),
                                  "WorldLoaderStateLabel",
                                  1);
    m_pStateLabel->SetY(rmode->viHeight / 2);    
    m_pStateLabel->SetFontSize(24);
    m_pStateLabel->SetCenteredX(true);
}

void WorldLoader::Load() {}

void WorldLoader::Update()
{
    m_state = m_nextState;

    switch (m_state)
    {
        case EWorldLoaderState::CHECK_WORLD_CASH:
            m_pStateLabel->SetText("Clean old world cash...");
            m_nextState = EWorldLoaderState::CLEAN_WORLD_CASH;
            break;
        case EWorldLoaderState::CLEAN_WORLD_CASH:
        {
            int value = FileSystem::RemoveDirectory(WORLD_PATH);
            if (value == -1)
            {
                WARNING("Couldn't not delete directory /world! Error: %s", strerror(errno));
            }
            m_nextState = EWorldLoaderState::TRY_CONNECTING_TO_SERVER;
            break;
        }
        case EWorldLoaderState::TRY_CONNECTING_TO_SERVER:
        {
            m_pStateLabel->SetText("Connecting to the server...");
            EventManager::AddListener(this, EVENT_SERVER_CONNECTED);
            EventManager::AddListener(this, EVENT_SERVER_CONNECTION_FAILED);
            NetworkManager::Get().Connect("192.168.0.143", 25565);
            PacketHandshake hs("DaeFennek", "192.168.0.143", 25565);
            hs.Send();
            m_nextState = EWorldLoaderState::WAIT_FOR_SERVER_LOGIN;
            break;
        }
        case EWorldLoaderState::WAIT_FOR_SERVER_LOGIN:
            m_pStateLabel->SetText("Connecting to the server...");
            break;
        case EWorldLoaderState::SERVER_CONNECTION_FAILED:
            m_pStateLabel->SetText("Failed to connect to the server");
            break;
        case EWorldLoaderState::CONNECTED_TO_SERVER:
            m_pStateLabel->SetText("Wait for chunk data from the server...");
            EventManager::Dispatch(EVENT_SEND_PLAYER_INFO_TO_SERVER);
            break;
        case EWorldLoaderState::LOAD_CHUNK_DATA_FROM_SERVER:
        {
            m_pStateLabel->SetText("Load chunk data from the server...");
            EventManager::Dispatch(EVENT_SEND_PLAYER_INFO_TO_SERVER);
            break;
        }
        case EWorldLoaderState::DONE:
            m_pStateLabel->SetText("Prepare World...");
            EventManager::Dispatch(EVENT_PREPARE_WORLD);
            break;
    }   
}

void WorldLoader::OnEvent(Event event)
{
    switch(event.ID)
    {
        case EVENT_SERVER_CONNECTED:
            EventManager::RemoveListener(this, EVENT_SERVER_CONNECTED);
            EventManager::RemoveListener(this, EVENT_SERVER_CONNECTION_FAILED);
            EventManager::AddListener(this, EVENT_RECEIVED_CHUNKS_FROM_SERVER);
            m_nextState = EWorldLoaderState::CONNECTED_TO_SERVER;
            break;
        case EVENT_SERVER_CONNECTION_FAILED:
            // todo handle
            EventManager::RemoveListener(this, EVENT_SERVER_CONNECTED);
            EventManager::RemoveListener(this, EVENT_SERVER_CONNECTION_FAILED);
            break;
        case EVENT_RECEIVED_CHUNKS_FROM_SERVER:
            EventManager::RemoveListener(this, EVENT_RECEIVED_CHUNKS_FROM_SERVER);
            EventManager::AddListener(this, EVENT_SERIALIZED_ALL_CHUNKS);
            m_nextState = EWorldLoaderState::LOAD_CHUNK_DATA_FROM_SERVER;
            break;
        case EVENT_SERIALIZED_ALL_CHUNKS:
            EventManager::RemoveListener(this, EVENT_SERIALIZED_ALL_CHUNKS);
            m_nextState = EWorldLoaderState::DONE;
            break;
    }
}

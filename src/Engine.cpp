/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/


#include <exception>
#include "Engine.h"
#include "utils/GameHelper.h"
#include "utils/Filesystem.h"
#include "net/NetworkManager.h"
#include "utils/Debug.h"

#include "net/packet/PacketHandshake.h"
#include "net/packet/PacketLogin.h"

Engine::Engine()
{
    m_bRunning = false;
    m_pSceneHandler = new SceneHandler();
    m_pInputHandler = new InputHandler();
    m_pFontHandler = new FontHandler();
    m_pBasicCommandHandler = new BasicCommandHandler();
}

Engine::~Engine() {}


void Engine::Start()
{
    m_bRunning = true;

    try
    {
        Init();

        m_pBasicCommandHandler->ExecuteCommand( SwitchToIntroCommand::Name() );

        while(m_bRunning)
        {
            uint64_t startFrameTime = ticks_to_millisecs(gettime());

            GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

            m_pInputHandler->Update();
            m_pSceneHandler->Update(m_millisecondsLastFrame / 1000.0f);
            NetworkManager::Get().Update();
            m_pSceneHandler->DrawScene();

            WiiPad* pad = m_pInputHandler->GetPadByID( WII_PAD_0 );
            u32 padButtonDown = pad->ButtonsDown();
            if ( padButtonDown & WPAD_BUTTON_HOME)
            {
                End();
            }

            PrintFps( 500, 25, m_pFontHandler->GetNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_YELLOW );

    #ifdef DEBUG
            PrintGameVersion(0, 25, m_pFontHandler->GetNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE );
    #endif

            GRRLIB_Render();
            CalculateFrameRate();

            m_millisecondsLastFrame = ticks_to_millisecs(gettime()) - startFrameTime;
            LOG("Frame Time: %f s", m_millisecondsLastFrame / 1000.0f);
        }

        NetworkManager::Get().Destroy();

        delete m_pBasicCommandHandler;
        delete m_pSceneHandler;
        delete m_pInputHandler;
        delete m_pFontHandler;

        GRRLIB_Exit();
        LOG("Graphics System uninitialized");
    }
    catch(const std::exception& ex)
    {
        ERROR("Engine crashed: %s", ex.what());
    }
    catch(...)
    {
        ERROR("Unkown Engine crash!");
    }
#ifdef DEBUG
    Debug::Release();
#endif
}

void Engine::End()
{
    m_bRunning = false;
}

void Engine::Init()
{    
    SYS_SetResetCallback([]() { Engine::Get().End(); });
    SYS_SetPowerCallback([]() { Engine::Get().End(); });

    FileSystem::Init();
    Debug::Init();    

    LOG("****** %s %s ******", GAME_NAME, BUILD_VERSION);
    NetworkManager::Get().Init();
    Debug::InitServer(true);

	GRRLIB_Init();
    GRRLIB_Settings.antialias = true;
    LOG("Graphics System initialized");
    LOG("Resolution x: %d y: %d", rmode->viWidth, rmode->viHeight);

    m_pFontHandler->Init();
    m_pInputHandler->Init();
    m_pSceneHandler->Init();
    m_pBasicCommandHandler->Init();
}

SceneHandler& Engine::GetSceneHandler()
{
    return *m_pSceneHandler;
}

InputHandler& Engine::GetInputHandler()
{
    return *m_pInputHandler;
}

FontHandler& Engine::GetFontHandler()
{
    return *m_pFontHandler;
}

BasicCommandHandler& Engine::GetBasicCommandHandler()
{
    return *m_pBasicCommandHandler;
}

SpriteStageManager& Engine::GetSpriteStageManager()
{
    return GetSceneHandler().GetCurrentScene()->GetSpriteStageManager();
}

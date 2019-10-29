#pragma once

#include "components/UiTextureElement.h"
#include "event/eventlistener.h"

enum class EWorldLoaderState : unsigned char
{   
    CHECK_WORLD_CACHE,
    CLEAN_WORLD_CACHE,
    TRY_CONNECTING_TO_SERVER,
    WAIT_FOR_SERVER_LOGIN,
    CONNECTED_TO_SERVER,
    SERVER_CONNECTION_FAILED,
    LOAD_CHUNK_DATA_FROM_SERVER,
    DONE
};

class WorldLoader : public UiTextureElement, public IEventListener
{
public:
    WorldLoader(const char* name, class Sprite* sprite);
    WorldLoader(const WorldLoader&) = delete;
    WorldLoader(WorldLoader&&) = delete;
    void operator=(const WorldLoader&) = delete;
    void operator=(WorldLoader&&) = delete;

    virtual void Load() override;
    virtual void Update() override;
    virtual void OnEvent(Event event) override;

    inline EWorldLoaderState GetState() const { return m_state; }

private:
    class Label* m_pStateLabel;
    EWorldLoaderState m_state;
    EWorldLoaderState m_nextState;    
};

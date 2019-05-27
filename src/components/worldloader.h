#pragma once

#include "UiTextureElement.h"
#include "../event/eventlistener.h"

enum class EWorldLoaderState : unsigned char
{   
    CHECK_WORLD_CASH,
    CLEAN_WORLD_CASH,
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
    virtual void Load() override;
    virtual void Update() override;
    virtual void OnEvent(Event event) override;

    inline EWorldLoaderState GetState() const { return m_state; }

private:
    EWorldLoaderState m_state;
    EWorldLoaderState m_nextState;
    class Label* m_pStateLabel;

};

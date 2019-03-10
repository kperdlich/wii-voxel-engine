#ifndef PACKETSPAWNPOSITION_H
#define PACKETSPAWNPOSITION_H

#include "Packet.h"
#include "PacketGlobals.h"
#include "../../Engine.h"
#include "../../entity/Player.h"
#include "../../scenes/Basic3DScene.h"
#include "../../utils/Debug.h"
#include "PacketPlayerPosition.h"
#include "PacketPlayer.h"

class PacketSpawnPosition : public Packet
{
public:
    PacketSpawnPosition() : Packet(PACKET_SPAWN_POSITION) {}

    void Read(const Socket& socket) override
    {
        m_x = socket.Read<int32_t>();
        m_y = socket.Read<int32_t>();
        m_z = socket.Read<int32_t>();
    }

    void Action() override
    {
        Basic3DScene* scene = dynamic_cast<Basic3DScene*>(Engine::Get().GetSceneHandler().GetCurrentScene());
        if (scene && scene->GetEntityHandler().GetPlayer())
        {
            CPlayer* p = static_cast<CPlayer*>(scene->GetEntityHandler().GetPlayer());
            //p->SetPosition(Vector3(m_x, m_y, m_z));
        }
        else
        {
            ERROR("Scene or player not initialized");
        }
    }

    Packet* CreateInstance() const override
    {
        return new PacketSpawnPosition();
    }

protected:
    void SendContent(const Socket &socket) const override {}
    int32_t m_x = 0, m_y = 0, m_z = 0;
};

#endif // PACKETSPAWNPOSITION_H

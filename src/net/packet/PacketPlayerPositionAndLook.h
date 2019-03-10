#ifndef PACKETPLAYERPOSITIONANDLOOK_H
#define PACKETPLAYERPOSITIONANDLOOK_H

#include "Packet.h"
#include "PacketGlobals.h"
#include "../../Engine.h"
#include "../../entity/Player.h"
#include "../../scenes/Basic3DScene.h"

class PacketPlayerPositionAndLook : public Packet
{
public:
    PacketPlayerPositionAndLook() : Packet(PACKET_PLAYER_POSITION_AND_LOOK) {}

    void Read(const Socket &socket) override
    {
        m_X = socket.Read<double>();
        m_Stance = socket.Read<double>();
        m_Y = socket.Read<double>();
        m_Z = socket.Read<double>();
        m_Yaw = socket.Read<float>();
        m_Pitch = socket.Read<float>();
        m_bOnGround = socket.Read<bool>();
    }
    void Action() override
    {
        Basic3DScene* scene = dynamic_cast<Basic3DScene*>(Engine::Get().GetSceneHandler().GetCurrentScene());
        if (scene && scene->GetEntityHandler().GetPlayer())
        {
            LOG("Server Player Pos update!");
            CPlayer* p = static_cast<CPlayer*>(scene->GetEntityHandler().GetPlayer());
            p->SetOnTheGround(m_bOnGround);
            p->SetPosition(Vector3(m_X, m_Y, m_Z));
            p->SetStance(m_Y+1.0);

            if (!p->IsPlayerSpawned())
                p->SetPlayerSpawned(true);
        }
        else
        {
            ERROR("Scene or player not initialized");
        }
        Send();
    }

    Packet *CreateInstance() const override
    {
        return new PacketPlayerPositionAndLook();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
        socket.Send<double>(m_X);
        socket.Send<double>(m_Y);
        socket.Send<double>(m_Stance);
        socket.Send<double>(m_Z);
        socket.Send<float>(m_Yaw);
        socket.Send<float>(m_Pitch);
        socket.Send<bool>(m_bOnGround);
    }

    double m_X = 0, m_Stance = 0, m_Y = 0, m_Z = 0;
    float m_Yaw = 0.0f, m_Pitch = 0.0f;
    bool m_bOnGround = false;

};

#endif // PACKETPLAYERPOSITIONANDLOOK_H

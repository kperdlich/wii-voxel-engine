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

    void Read(const Session &session) override
    {
        m_X = session.Read<double>();
        m_Stance = session.Read<double>();
        m_Y = session.Read<double>();
        m_Z = session.Read<double>();
        m_Yaw = session.Read<float>();
        m_Pitch = session.Read<float>();
        m_bOnGround = session.Read<bool>();
    }
    void Action() override
    {
        Basic3DScene* scene = dynamic_cast<Basic3DScene*>(Engine::Get().GetSceneHandler().GetCurrentScene());
        if (scene && scene->GetEntityHandler().GetPlayer())
        {
            CPlayer* p = static_cast<CPlayer*>(scene->GetEntityHandler().GetPlayer());
            p->SetOnTheGround(m_bOnGround);
            p->SetPosition(Vector3(m_X, m_Y, m_Z));

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
    void SendContent(const Session &session) const override
    {
        session.Send<double>(m_X);
        session.Send<double>(m_Y);
        session.Send<double>(m_Stance);
        session.Send<double>(m_Z);
        session.Send<float>(m_Yaw);
        session.Send<float>(m_Pitch);
        session.Send<bool>(m_bOnGround);
    }

    double m_X = 0, m_Stance = 0, m_Y = 0, m_Z = 0;
    float m_Yaw = 0.0f, m_Pitch = 0.0f;
    bool m_bOnGround = false;

};

#endif // PACKETPLAYERPOSITIONANDLOOK_H

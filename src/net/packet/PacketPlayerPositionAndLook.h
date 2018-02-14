#ifndef PACKETPLAYERPOSITIONANDLOOK_H
#define PACKETPLAYERPOSITIONANDLOOK_H

#include "Packet.h"
#include "PacketGlobals.h"

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

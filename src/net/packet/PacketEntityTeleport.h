#ifndef PACKETTELEPORT_H
#define PACKETTELEPORT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityTeleport : public Packet
{
public:
    PacketEntityTeleport() : Packet(PACKET_ENTITY_TELEPORT) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_Yaw = session.Read<char>();
        m_Pitch = session.Read<char>();
    }

    void Action() const override
    {
    }

    Packet *CreateInstance() const override
    {
        return new PacketEntityTeleport();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    int32_t m_X = 0, m_Y = 0, m_Z = 0;
    char m_Yaw = 0, m_Pitch = 0;
};

#endif // PACKETTELEPORT_H

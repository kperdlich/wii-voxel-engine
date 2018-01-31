#ifndef PACKETENTITYLOOKANDRELATIVEMOVE_H
#define PACKETENTITYLOOKANDRELATIVEMOVE_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityLookAndRelativeMove : public Packet
{
public:
    PacketEntityLookAndRelativeMove() : Packet(PACKET_ENTITY_LOOK_RELATIVE_MOVE) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_DX = session.Read<char>();
        m_DY = session.Read<char>();
        m_DZ = session.Read<char>();
        m_Yaw = session.Read<char>();
        m_Pitch = session.Read<char>();
    }

    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketEntityLookAndRelativeMove();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    char m_Yaw = 0, m_Pitch = 0;
    char m_DX = 0, m_DY = 0, m_DZ = 0;
};

#endif // PACKETENTITYLOOKANDRELATIVEMOVE_H

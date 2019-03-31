#ifndef PACKETENTITYHEADLOOK_H
#define PACKETENTITYHEADLOOK_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityHeadLook : public Packet
{
public:
    PacketEntityHeadLook() : Packet(PACKET_ENTITY_HEAD_LOOK) {}

    void Read(const Socket &socket) override
    {
        m_EID = socket.Read<int32_t>();
        m_HeadYaw = socket.Read<char>();
    }

    void Action() override
    {
    }

    Packet *CreateInstance() const override
    {
        return new PacketEntityHeadLook();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
    }

    int32_t m_EID = 0;
    char m_HeadYaw = 0;
};

#endif // PACKETENTITYHEADLOOK_H

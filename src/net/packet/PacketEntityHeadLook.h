#ifndef PACKETENTITYHEADLOOK_H
#define PACKETENTITYHEADLOOK_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityHeadLook : public Packet
{
public:
    PacketEntityHeadLook() : Packet(PACKET_ENTITY_HEAD_LOOK) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_HeadYaw = session.Read<char>();
    }

    void Action() override
    {
    }

    Packet *CreateInstance() const override
    {
        return new PacketEntityHeadLook();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    char m_HeadYaw = 0;
};

#endif // PACKETENTITYHEADLOOK_H

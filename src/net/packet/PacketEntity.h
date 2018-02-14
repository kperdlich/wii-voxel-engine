#ifndef PACKETENTITY_H
#define PACKETENTITY_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntity : public Packet
{
public:
    PacketEntity() : Packet(PACKET_ENTITY) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
    }
    void Action() override
    {
    }
    Packet* CreateInstance() const override
    {
        return new PacketEntity();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }
    int32_t m_EID = 0;
};

#endif // PACKETENTITY_H

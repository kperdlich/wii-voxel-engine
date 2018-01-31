#ifndef PACKETENTITYSTATUS_H
#define PACKETENTITYSTATUS_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityStatus : public Packet
{
public:
    PacketEntityStatus() : Packet(PACKET_ENTITY_STATUS) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_EntityStatus = session.Read<char>();
    }

    void Action() const override
    {
    }

    Packet* CreateInstance() const override
    {
        return new PacketEntityStatus();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    char m_EntityStatus = 0;
};

#endif // PACKETENTITYSTATUS_H

#ifndef PACKETENTITYLOOK_H
#define PACKETENTITYLOOK_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityLook : public Packet
{
public:
    PacketEntityLook() : Packet(PACKET_ENTITY_LOOK) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Yaw = session.Read<char>();
        m_Pitch = session.Read<char>();
    }

    void Action() override
    {
    }

    Packet* CreateInstance() const override
    {
        return new PacketEntityLook();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    char m_Yaw = 0, m_Pitch = 0;

};

#endif // PACKETENTITYLOOK_H


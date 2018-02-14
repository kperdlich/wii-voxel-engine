#ifndef PACKETDESTROYENTITY_H
#define PACKETDESTROYENTITY_H


#include "Packet.h"
#include "PacketGlobals.h"

class PacketDestroyEntity : public Packet
{
public:
    PacketDestroyEntity() : Packet(PACKET_DESTROY_ENTITY) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
    }
    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketDestroyEntity();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
};

#endif // PACKETDESTROYENTITY_H

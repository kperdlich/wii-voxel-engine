#ifndef PACKETENTITYVELOCITY_H
#define PACKETENTITYVELOCITY_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityVelocity : public Packet
{
public:
    PacketEntityVelocity() : Packet(PACKET_ENTITY_VELOCITY) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_VelocityX = session.Read<int16_t>();
        m_VelocityY = session.Read<int16_t>();
        m_VelocityZ = session.Read<int16_t>();
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketEntityVelocity();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    int16_t m_VelocityX = 0, m_VelocityY = 0, m_VelocityZ = 0;
};

#endif // PACKETENTITYVELOCITY_H

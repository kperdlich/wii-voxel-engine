#ifndef PACKETSETEXPERIENCE_H
#define PACKETSETEXPERIENCE_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSetExperience : public Packet
{
public:
    PacketSetExperience() : Packet(PACKET_SET_EXPERIENCE) {}

    void Read(const Session &session) override
    {
        m_ExperienceBar = session.Read<float>();
        m_Level = session.Read<uint16_t>();
        m_TotalExperience = session.Read<uint16_t>();
    }
    void Action() const override
    {
    }
    Packet* CreateInstance() const override
    {
        return new PacketSetExperience();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    float m_ExperienceBar = 0.0f;
    uint16_t m_Level = 0, m_TotalExperience = 0;

};

#endif // PACKETSETEXPERIENCE_H

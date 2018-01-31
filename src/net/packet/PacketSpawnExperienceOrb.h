#ifndef PACKETSPAWNEXPERIENCEORB_H
#define PACKETSPAWNEXPERIENCEORB_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSpawnExperienceOrb : public Packet
{
public:
    PacketSpawnExperienceOrb() : Packet(PACKET_SPAWN_EXPERIENCE_ORB) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_Count = session.Read<int16_t>();
    }
    void Action() const override
    {

    }

    Packet *CreateInstance() const override
    {
        return new PacketSpawnExperienceOrb();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }

    int32_t m_EID = 0, m_X = 0, m_Y = 0, m_Z = 0;
    int16_t m_Count = 0;
};

#endif // PACKETSPAWNEXPERIENCEORB_H

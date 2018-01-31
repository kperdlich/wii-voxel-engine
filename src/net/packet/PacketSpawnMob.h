#ifndef PACKETSPAWNMOB_H
#define PACKETSPAWNMOB_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSpawnMob : public Packet
{
public:
    PacketSpawnMob() : Packet(PACKET_SPAWN_MOB) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Type = session.Read<char>();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_Yaw = session.Read<char>();
        m_Pitch = session.Read<char>();
        m_HeadYaw = session.Read<char>();
        // todo read metadata
    }
    void Action() const override
    {

    }
    Packet* CreateInstance() const override
    {
        return new PacketSpawnMob();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }

    int32_t m_EID = 0;
    char m_Type = 0;
    int32_t m_X = 0, m_Y = 0, m_Z = 0;
    char m_Yaw = 0, m_Pitch = 0, m_HeadYaw;

};

#endif // PACKETSPAWNMOB_H

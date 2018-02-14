#ifndef PACKETSPAWNNAMEDENTITY_H
#define PACKETSPAWNNAMEDENTITY_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSpawnNamedEntity : public Packet
{
public:
    PacketSpawnNamedEntity() : Packet(PACKET_SPAWN_NAMED_ENTITY) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_PlayerName = session.ReadString();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_Yaw = session.Read<char>();
        m_Pitch = session.Read<char>();
        m_CurrentItem = session.Read<int16_t>();
    }
    void Action() override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketSpawnNamedEntity();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }

    int32_t m_EID = 0;
    std::string m_PlayerName;
    int32_t m_X = 0, m_Y = 0, m_Z = 0;
    char m_Yaw = 0, m_Pitch = 0;
    int16_t m_CurrentItem = 0;


};

#endif // PACKETSPAWNNAMEDENTITY_H

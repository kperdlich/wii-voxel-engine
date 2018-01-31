#ifndef PACKETRESPAWN_H
#define PACKETRESPAWN_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketRespawn : public Packet
{
public:
    PacketRespawn() : Packet(PACKET_RESPAWN) {}

    void Read(const Session &session) override
    {
        m_Dimension = session.Read<int32_t>();
        m_Difficulty = session.Read<char>();
        m_CreativeMode = session.Read<char>();
        m_WorldHeight = session.Read<int16_t>();
        m_LevelType = session.ReadString();
    }

    void Action() const override
    {

    }

    Packet *CreateInstance() const override
    {
        return new PacketRespawn();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }

    int32_t m_Dimension = 0;
    char m_Difficulty = 0, m_CreativeMode = 0;
    int16_t m_WorldHeight = 0;
    std::string m_LevelType;

};

#endif // PACKETRESPAWN_H

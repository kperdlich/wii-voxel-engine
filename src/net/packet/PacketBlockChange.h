#ifndef PACKETBLOCKCHANGE_H
#define PACKETBLOCKCHANGE_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketBlockChange : public Packet
{
public:
    PacketBlockChange() : Packet(PACKET_BLOCK_CHANGE) {}

    void Read(const Session &session) override
    {
        m_X = session.Read<int32_t>();
        m_Y = session.Read<char>();
        m_Z = session.Read<int32_t>();
        m_BlockType = session.Read<char>();
        m_BlockMetadata = session.Read<char>();
    }

    void Action() override
    {
    }

    Packet* CreateInstance() const override
    {
        return new PacketBlockChange();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_X = 0, m_Z = 0;
    char m_Y = 0, m_BlockType = 0, m_BlockMetadata = 0;
};

#endif // PACKETBLOCKCHANGE_H

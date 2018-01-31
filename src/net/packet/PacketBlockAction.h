#ifndef PACKETBLOCKACTION_H
#define PACKETBLOCKACTION_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketBlockAction : public Packet
{
public:
    PacketBlockAction() : Packet(PACKET_BLOCK_ACTION) {}

    void Read(const Session &session) override
    {
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_Byte_1 = session.Read<char>();
        m_Byte_2 = session.Read<char>();
    }

    void Action() const override
    {
    }

    Packet *CreateInstance() const override
    {
        return new PacketBlockAction();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_X = 0;
    int16_t m_Y = 0;
    int32_t m_Z = 0;
    char m_Byte_1 = 0, m_Byte_2 = 0;
};

#endif // PACKETBLOCKACTION_H

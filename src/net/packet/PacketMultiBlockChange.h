#ifndef PACKETMULTIBLOCKCHANGE_H
#define PACKETMULTIBLOCKCHANGE_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketMultiBlockChange : public Packet
{
public:
    PacketMultiBlockChange() : Packet(PACKET_MULTI_BLOCK_CHANGE) {}

    ~PacketMultiBlockChange()
    {
        if (m_Data)
            free(m_Data);
    }

    void Read(const Session &session) override
    {
        m_ChunkX = session.Read<int32_t>();
        m_ChunkZ = session.Read<int32_t>();
        m_RecordCount = session.Read<int16_t>();
        m_DataSize = session.Read<int32_t>();
        m_Data = malloc(m_DataSize);
        session.Read(m_Data, m_DataSize);
    }

    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketMultiBlockChange();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_ChunkX = 0, m_ChunkZ = 0;
    int16_t m_RecordCount = 0;
    int32_t m_DataSize = 0;
    void* m_Data = nullptr;
};

#endif // PACKETMULTIBLOCKCHANGE_H

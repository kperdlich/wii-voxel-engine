#ifndef PACKETCHUNKALLOCATION_H
#define PACKETCHUNKALLOCATION_H

#include "Packet.h"
#include "PacketGlobals.h"
#include "../../scenes/InGameScene.h"
#include "../../world/GameWorld.h"
#include "../../world/chunk/Chunk.h"

class PacketChunkAllocation : public Packet
{
public:
    PacketChunkAllocation() : Packet(PACKET_CHUNK_ALLOCATION) {}

    void Read(const Socket& socket) override
    {
        m_x     =   socket.Read<int32_t>();
        m_y     =   socket.Read<int32_t>();
        m_bMode =   socket.Read<bool>();
    }

    void Action() override
    {        
    }

    Packet *CreateInstance() const override
    {
        return new PacketChunkAllocation();
    }

protected:
    void SendContent(const Socket &socket) const override {}
    int32_t m_x = 0, m_y = 0;
    bool m_bMode = false;
};

#endif // PACKETCHUNKALLOCATION_H

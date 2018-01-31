#ifndef PACKETCHUNKDATA_H
#define PACKETCHUNKDATA_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketChunkData : public Packet
{
public:
    PacketChunkData() : Packet(PACKET_CHUNK_DATA) {}

    void Read(const Session &session) override
    {
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketChunkData();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }
};

#endif // PACKETCHUNKDATA_H

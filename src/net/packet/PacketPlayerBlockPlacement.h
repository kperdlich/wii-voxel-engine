#ifndef PACKETPLAYERBLOCKPLACEMENT_H
#define PACKETPLAYERBLOCKPLACEMENT_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayerBlockPlacement : public Packet
{
public:
    PacketPlayerBlockPlacement() : Packet(PACKET_PLAYER_BLOCK_PLACEMENT) {}

    void Read(const Session &session) override
    {

    }
    void Action() const override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketPlayerBlockPlacement();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }
};

#endif // PACKETPLAYERBLOCKPLACEMENT_H

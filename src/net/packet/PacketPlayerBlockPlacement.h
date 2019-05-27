#pragma once

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayerBlockPlacement : public Packet
{
public:
    PacketPlayerBlockPlacement() : Packet(PACKET_PLAYER_BLOCK_PLACEMENT) {}

    void Read(const Socket &socket) override
    {

    }
    void Action() override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketPlayerBlockPlacement();
    }

protected:
    void SendContent(const Socket &socket) const override
    {

    }
};

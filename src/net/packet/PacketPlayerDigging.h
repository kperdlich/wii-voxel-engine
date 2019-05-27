#pragma once

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayerDigging : public Packet
{
public:
    PacketPlayerDigging() : Packet(PACKET_PLAYER_DIGGING) {}

    void Read(const Socket &socket) override
    {

    }
    void Action() override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketPlayerDigging();
    }

protected:
    void SendContent(const Socket &socket) const override
    {

    }
};

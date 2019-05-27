#pragma once

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayerLook : public Packet
{
public:
    PacketPlayerLook() : Packet(PACKET_PLAYER_LOOK) {}

    void Read(const Socket &socket) override
    {
    }

    void Action() override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketPlayerLook();
    }

protected:
    void SendContent(const Socket &socket) const override
    {

    }
};

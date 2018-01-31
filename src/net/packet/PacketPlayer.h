#ifndef PACKETPLAYER_H
#define PACKETPLAYER_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayer : public Packet
{
public:
    PacketPlayer() : Packet(PACKET_PLAYER) {}

    void Read(const Session &session) override
    {

    }
    void Action() const override
    {

    }
    Packet *CreateInstance() const override
    {
       return new PacketPlayer();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }
};

#endif // PACKETPLAYER_H

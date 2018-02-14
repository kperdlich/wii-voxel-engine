#ifndef PAKCETPLAYERDIGGING_H
#define PAKCETPLAYERDIGGING_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayerDigging : public Packet
{
public:
    PacketPlayerDigging() : Packet(PACKET_PLAYER_DIGGING) {}

    void Read(const Session &session) override
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
    void SendContent(const Session &session) const override
    {

    }
};

#endif // PAKCETPLAYERDIGGING_H

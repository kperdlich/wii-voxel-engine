#ifndef PACKETPLAYERLOOK_H
#define PACKETPLAYERLOOK_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayerLook : public Packet
{
public:
    PacketPlayerLook() : Packet(PACKET_PLAYER_LOOK) {}

    void Read(const Session &session) override
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
    void SendContent(const Session &session) const override
    {

    }
};

#endif // PACKETPLAYERLOOK_H

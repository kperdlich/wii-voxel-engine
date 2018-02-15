#ifndef PACKETPLAYER_H
#define PACKETPLAYER_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayer : public Packet
{
public:
    PacketPlayer(bool onGround = false) : Packet(PACKET_PLAYER), m_bOnGround(onGround) {}

    void Read(const Session &session) override
    {

    }
    void Action() override
    {

    }
    Packet *CreateInstance() const override
    {
       return new PacketPlayer();
    }

protected:
    void SendContent(const Session &session) const override
    {
        session.Send<bool>(m_bOnGround);
    }

    bool m_bOnGround;
};

#endif // PACKETPLAYER_H
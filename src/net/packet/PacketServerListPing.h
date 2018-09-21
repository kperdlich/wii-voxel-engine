#ifndef PACKETSERVERLISTPING_H
#define PACKETSERVERLISTPING_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketServerListPing : public Packet
{
public:
    PacketServerListPing() : Packet(PACKET_SERVER_LIST_PING) {}

    void Read(const Socket &socket) override
    {
    }
    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketServerListPing();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
    }
};

#endif // PACKETSERVERLISTPING_H

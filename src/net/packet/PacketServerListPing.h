#ifndef PACKETSERVERLISTPING_H
#define PACKETSERVERLISTPING_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketServerListPing : public Packet
{
public:
    PacketServerListPing() : Packet(PACKET_SERVER_LIST_PING) {}

    void Read(const Session &session) override
    {
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketServerListPing();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }
};

#endif // PACKETSERVERLISTPING_H

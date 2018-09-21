#ifndef PACKETDISCONNECT_H
#define PACKETDISCONNECT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketDisconnect : public Packet
{
public:
    PacketDisconnect() : Packet(PACKET_DISCONNECT) {}

    void Read(const Socket &socket) override
    {
        m_Reason = socket.ReadString();
    }

    void Action() override
    {        

    }

    Packet *CreateInstance() const override
    {
        return new PacketDisconnect();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
    }

    std::string m_Reason;
};

#endif // PACKETDISCONNECT_H

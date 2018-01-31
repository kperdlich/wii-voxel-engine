#ifndef PACKETDISCONNECT_H
#define PACKETDISCONNECT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketDisconnect : public Packet
{
public:
    PacketDisconnect() : Packet(PACKET_DISCONNECT) {}

    void Read(const Session &session) override
    {
        m_Reason = session.ReadString();
    }

    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketDisconnect();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    std::string m_Reason;
};

#endif // PACKETDISCONNECT_H

#ifndef PACKETTIMEUPDATE_H
#define PACKETTIMEUPDATE_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketTimeUpdate : public Packet
{
public:
    PacketTimeUpdate() : Packet(PACKET_TIME_UPDATE) {}

    void Read(const Session &session) override
    {
        m_time = session.Read<int64_t>();
    }

    void Action() const override
    {
        // todo implement
    }

    Packet *CreateInstance() const override
    {
        return new PacketTimeUpdate();
    }

protected:
    int64_t m_time = 0;
    void SendContent(const Session &session) const override {}
};

#endif // PACKETTIMEUPDATE_H

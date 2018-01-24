#ifndef PACKETKEEPALIVE_H
#define PACKETKEEPALIVE_H

#include "Packet.h"

class PacketKeepAlive : public Packet
{
public:
    PacketKeepAlive(int32_t id = 0) : Packet(0x00), m_ID(id) {}
protected:
    void SendContent(const Session& session) override
    {
        session.SendUInt(m_ID);
    }
private:
    int32_t m_ID = 0;
};

#endif // PACKETKEEPALIVE_H

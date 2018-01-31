#ifndef PACKETINCREMENTSTATISTIC_H
#define PACKETINCREMENTSTATISTIC_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketIncrementStatistic : public Packet
{
public:
    PacketIncrementStatistic() : Packet(PACKET_INCREMENT_STATISTICS) {}

    void Read(const Session &session) override
    {
        m_StatisticID = session.Read<int32_t>();
        m_Amount = session.Read<char>();
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketIncrementStatistic();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

   int32_t m_StatisticID = 0;
   char m_Amount = 0;
};

#endif // PACKETINCREMENTSTATISTIC_H

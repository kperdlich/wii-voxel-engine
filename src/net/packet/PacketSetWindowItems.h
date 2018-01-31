#ifndef PACKETSETWINDOWITEMS_H
#define PACKETSETWINDOWITEMS_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSetWindowItems : public Packet
{
public:
     PacketSetWindowItems() : Packet(PACKET_SET_WINDOW_ITEMS) {}

     void Read(const Session &session) override
     {
         m_WindowID = session.Read<char>();
         m_Count = session.Read<int16_t>();
         // todo add slot data
     }
     void Action() const override
     {
     }
     Packet *CreateInstance() const override
     {
         return new PacketSetWindowItems();
     }

protected:
     void SendContent(const Session &session) const override
     {
     }

     char m_WindowID = 0;
     int16_t m_Count = 0;
     // todo add slot data
};

#endif // PACKETSETWINDOWITEMS_H

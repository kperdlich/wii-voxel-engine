#ifndef PACKETSETWINDOWITEMS_H
#define PACKETSETWINDOWITEMS_H

#include <vector>
#include "Packet.h"
#include "PacketGlobals.h"

class PacketSetWindowItems : public Packet
{
public:
     PacketSetWindowItems() : Packet(PACKET_SET_WINDOW_ITEMS) {}

     ~PacketSetWindowItems()
     {
         m_SlotData.clear();
     }

     void Read(const Session &session) override
     {
         m_WindowID = session.Read<char>();
         m_Count = session.Read<int16_t>();
         ReadSlotData(m_SlotData, m_Count, session);
     }

     void Action() override
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
     std::vector<SlotData> m_SlotData;
};

#endif // PACKETSETWINDOWITEMS_H

#ifndef PACKETSETSLOT_H
#define PACKETSETSLOT_H

#include <vector>
#include "Packet.h"
#include "PacketGlobals.h"

class PacketSetSlot : public Packet
{
public:
    PacketSetSlot() : Packet(PACKET_SET_SLOT) {}

    void Read(const Session &session) override
    {
        m_WindowID = session.Read<char>();
        m_Slot = session.Read<int16_t>();
        ReadSlotData(m_SlotData, session);

    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketSetSlot();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    char m_WindowID = 0;
    int16_t m_Slot = 0;
    SlotData m_SlotData;
};

#endif // PACKETSETSLOT_H

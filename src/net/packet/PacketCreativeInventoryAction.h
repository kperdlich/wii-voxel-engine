#ifndef PACKETCREATIVEINVENTORYACTION_H
#define PACKETCREATIVEINVENTORYACTION_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketCreativeInventoryAction : public Packet
{
public:
    PacketCreativeInventoryAction() : Packet(PACKET_CREATIVE_INVENTORY_ACTION) {}

    void Read(const Session &session) override
    {
        m_Slot = session.Read<int16_t>();
        ReadSlotData(m_SlotData, session);
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketCreativeInventoryAction();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int16_t m_Slot = 0;
    SlotData m_SlotData;
};

#endif // PACKETCREATIVEINVENTORYACTION_H


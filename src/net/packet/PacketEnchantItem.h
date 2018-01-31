#ifndef PACKETENCHANTITEM_H
#define PACKETENCHANTITEM_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEnchantItem : public Packet
{
public:
    PacketEnchantItem() : Packet(PACKET_ENCHANT_ITEM) {}

    // Packet interface
public:
    void Read(const Session &session) override
    {
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketEnchantItem();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }
};

#endif // PACKETENCHANTITEM_H

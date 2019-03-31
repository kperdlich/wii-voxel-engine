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
    void Read(const Socket &socket) override
    {
    }
    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketEnchantItem();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
    }
};

#endif // PACKETENCHANTITEM_H

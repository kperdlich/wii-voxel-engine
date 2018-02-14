#ifndef PACKETENTITYEQUIPMENT_H
#define PACKETENTITYEQUIPMENT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityEquipment : public Packet
{
public:
    PacketEntityEquipment() : Packet(PACKET_ENTITY_EQUIPMENT) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Slot = session.Read<int16_t>();
        m_ItemID = session.Read<int16_t>();
        m_Damage = session.Read<int16_t>();
    }
    void Action() override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketEntityEquipment();
    }

protected:
    int32_t m_EID = 0;
    int16_t m_Slot = 0, m_ItemID = 0, m_Damage = 0;


    void SendContent(const Session &session) const override
    {

    }
};

#endif // PACKETENTITYEQUIPMENT_H

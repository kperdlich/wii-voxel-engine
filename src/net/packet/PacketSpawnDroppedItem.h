#ifndef PACKETSPAWNDROPPEDITEM_H
#define PACKETSPAWNDROPPEDITEM_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSpawnDroppedItem : public Packet
{
public:
    PacketSpawnDroppedItem() : Packet(PACKET_SPAWN_DROPPED_ITEM) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Item = session.Read<int16_t>();
        m_Count = session.Read<char>();
        m_Data = session.Read<int16_t>();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_Rotation = session.Read<char>();
        m_Pitch = session.Read<char>();
        m_Roll = session.Read<char>();
    }

    void Action() const override
    {

    }

    Packet *CreateInstance() const override
    {
        return new PacketSpawnDroppedItem();
    }

protected:
    void SendContent(const Session &session) const override {}

    int32_t m_EID = 0;
    int16_t m_Item = 0;
    char m_Count = 0;
    int16_t m_Data = 0;
    int32_t m_X = 0, m_Y = 0, m_Z = 0;
    char m_Rotation = 0;
    char m_Pitch = 0;
    char m_Roll = 0;

};

#endif // PACKETSPAWNDROPPEDITEM_H

#ifndef PACKETSPAWNOBJECT_H
#define PACKETSPAWNOBJECT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSpawnObject : public Packet
{
public:
    PacketSpawnObject() : Packet(PACKET_SPAWN_OBJECT) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Type = session.Read<char>();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_AdditionalData = session.Read<int32_t>();
    }
    void Action() const override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketSpawnObject();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }

    int32_t m_EID = 0;
    char m_Type = 0;
    int32_t m_X = 0, m_Y = 0, m_Z = 0;
    int32_t m_AdditionalData = 0;
};

#endif // PACKETSPAWNOBJECT_H

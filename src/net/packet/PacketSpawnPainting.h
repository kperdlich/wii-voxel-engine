#ifndef PACKETSPAWNPAINTING_H
#define PACKETSPAWNPAINTING_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSpawnPainting : public Packet
{
public:
    PacketSpawnPainting() : Packet(PACKET_SPAWN_PAINTING) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Title = session.ReadString();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_Direction = session.Read<int32_t>();
    }
    void Action() const override
    {

    }
    Packet* CreateInstance() const override
    {
        return new PacketSpawnPainting();
    }

protected:
    void SendContent(const Session &session) const override {}

    int32_t m_EID = 0;
    std::string m_Title;
    int32_t m_X = 0, m_Y = 0, m_Z = 0, m_Direction = 0;
};

#endif // PACKETSPAWNPAINTING_H

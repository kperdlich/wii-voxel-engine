#ifndef PACKETTHUNDERBOLT_H
#define PACKETTHUNDERBOLT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketThunderbolt : public Packet
{
public:
    PacketThunderbolt() : Packet(PACKET_THUNDERBOLT) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Unkown = session.Read<char>();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketThunderbolt();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    char m_Unkown = 0;
    int32_t m_X = 0, m_Y = 0, m_Z = 0;
};

#endif // PACKETTHUNDERBOLT_H

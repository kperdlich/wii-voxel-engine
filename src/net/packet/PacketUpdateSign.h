#ifndef PACKETUPDATESIGN_H
#define PACKETUPDATESIGN_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketUpdateSign : public Packet
{
public:
    PacketUpdateSign() : Packet(PACKET_UPDATE_SIGN) {}

    void Read(const Session &session) override
    {
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int16_t>();
        m_Z = session.Read<int32_t>();
        m_Text1 = session.ReadString();
        m_Text2 = session.ReadString();
        m_Text3 = session.ReadString();
        m_Text4 = session.ReadString();
    }

    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketUpdateSign();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_X = 0, m_Z = 0;
    int16_t m_Y = 0;
    std::string  m_Text1, m_Text2, m_Text3, m_Text4;
};

#endif // PACKETUPDATESIGN_H

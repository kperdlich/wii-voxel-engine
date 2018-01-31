#ifndef PACKETUSEBED_H
#define PACKETUSEBED_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketUseBed : public Packet
{
public:
    PacketUseBed() : Packet(PACKET_USE_BED) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Unkown = session.Read<char>();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<char>();
        m_Z = session.Read<int32_t>();
    }
    void Action() const override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketUseBed();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }

   int32_t m_EID = 0;
   char m_Unkown = 0;
   int32_t m_X = 0;
   char m_Y = 0;
   int32_t m_Z = 0;
};

#endif // PACKETUSEBED_H

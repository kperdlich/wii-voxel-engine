#ifndef PACKETANIMATION_H
#define PACKETANIMATION_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketAnimation : public Packet
{
public:
    PacketAnimation() : Packet(PACKET_ANIMATION) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_Animation = session.Read<char>();
    }
    void Action() override
    {

    }

    Packet *CreateInstance() const override
    {
        return new PacketAnimation();
    }

protected:
    void SendContent(const Session &session) const override
    {

    }

    int32_t m_EID = 0;
    char m_Animation = 0;
};

#endif // PACKETANIMATION_H

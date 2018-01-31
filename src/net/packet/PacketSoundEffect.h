#ifndef PACKETSOUNDEFFECT_H
#define PACKETSOUNDEFFECT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketSoundEffect : public Packet
{
public:
    PacketSoundEffect() : Packet(PACKET_SOUND_EFFECT) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_X = session.Read<int32_t>();
        m_Y = session.Read<char>();
        m_Z = session.Read<int32_t>();
        m_Data = session.Read<int32_t>();

    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketSoundEffect();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    int32_t m_X = 0;
    char m_Y = 0;
    int32_t m_Z = 0;
    int32_t m_Data = 0;
};

#endif // PACKETSOUNDEFFECT_H

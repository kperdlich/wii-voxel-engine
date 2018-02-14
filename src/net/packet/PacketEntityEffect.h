#ifndef PACKETENTITYEFFECT_H
#define PACKETENTITYEFFECT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityEffect : public Packet
{
public:
    PacketEntityEffect() : Packet(PACKET_ENTITY_EFFECT) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_EffectID = session.Read<char>();
        m_Amplifier = session.Read<char>();
        m_Duration = session.Read<int16_t>();
    }
    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketEntityEffect();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    char m_EffectID = 0, m_Amplifier = 0;
    int16_t m_Duration = 0;
};

#endif // PACKETENTITYEFFECT_H

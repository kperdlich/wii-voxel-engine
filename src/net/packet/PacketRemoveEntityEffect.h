#ifndef PACKETREMOVEENTITYEFFECT_H
#define PACKETREMOVEENTITYEFFECT_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketRemoveEntityEffect : public Packet
{
public:
    PacketRemoveEntityEffect() : Packet(PACKET_REMOVE_ENTITY_EFFECT) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_EffectID = session.Read<char>();
    }

    void Action() const override
    {
    }

    Packet *CreateInstance() const override
    {
        return new PacketRemoveEntityEffect();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;
    char m_EffectID = 0;
};

#endif // PACKETREMOVEENTITYEFFECT_H

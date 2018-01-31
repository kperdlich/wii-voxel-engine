#ifndef PLAYERABILITES_H
#define PLAYERABILITES_H

#include "Packet.h"
#include "PacketGlobals.h"
#include "../../utils/Debug.h"

class PacketPlayerAbilites : public Packet
{
public:
    PacketPlayerAbilites() : Packet(PACKET_PLAYER_ABILITIES) {}

    void Read(const Session &session) override
    {
        m_bInvulnerability = session.Read<bool>();
        m_bIsflying = session.Read<bool>();
        m_bCanfly = session.Read<bool>();
        m_bInstantDestroy = session.Read<bool>();
    }

    void Action() const override
    {
        // todo implement
    }

    Packet *CreateInstance() const override
    {
        return new PacketPlayerAbilites();
    }

protected:
    void SendContent(const Session &session) const override
    {
        // todo implement
    }

    bool m_bInvulnerability = false,
    m_bIsflying = false,
    m_bCanfly = false,
    m_bInstantDestroy = false;
};

#endif // PLAYERABILITES_H

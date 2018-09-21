#ifndef PLAYERABILITES_H
#define PLAYERABILITES_H

#include "Packet.h"
#include "PacketGlobals.h"
#include "../../utils/Debug.h"

class PacketPlayerAbilites : public Packet
{
public:
    PacketPlayerAbilites() : Packet(PACKET_PLAYER_ABILITIES) {}

    void Read(const Socket &socket) override
    {
        m_bInvulnerability = socket.Read<bool>();
        m_bIsflying = socket.Read<bool>();
        m_bCanfly = socket.Read<bool>();
        m_bInstantDestroy = socket.Read<bool>();
    }

    void Action() override
    {
        // todo implement
    }

    Packet *CreateInstance() const override
    {
        return new PacketPlayerAbilites();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
        // todo implement
    }

    bool m_bInvulnerability = false,
    m_bIsflying = false,
    m_bCanfly = false,
    m_bInstantDestroy = false;
};

#endif // PLAYERABILITES_H

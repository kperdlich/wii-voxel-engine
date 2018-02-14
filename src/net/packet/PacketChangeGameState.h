#ifndef PACKETCHANGEGAMESTATE_H
#define PACKETCHANGEGAMESTATE_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketChangeGameState : public Packet
{
public:
    PacketChangeGameState() : Packet(PACKET_CHANGE_GAME_STATE) {}

    void Read(const Session &session) override
    {
        m_Reason = session.Read<char>();
        m_GameMode = session.Read<char>();
    }

    void Action() override
    {
    }

    Packet *CreateInstance() const override
    {
        return new PacketChangeGameState();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    char m_Reason = 0, m_GameMode = 0;

};

#endif // PACKETCHANGEGAMESTATE_H

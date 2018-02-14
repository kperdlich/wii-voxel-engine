#ifndef PACKETPLAYERLISTITEM_H
#define PACKETPLAYERLISTITEM_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketPlayerListItem : public Packet
{
public:
    PacketPlayerListItem() : Packet(PACKET_PLAYER_LIST_ITEM) {}

    void Read(const Session &session) override
    {
        m_PlayerName = session.ReadString();
        m_bOnline = session.Read<bool>();
        m_Ping = session.Read<int16_t>();
    }
    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketPlayerListItem();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    std::string m_PlayerName;
    bool m_bOnline = false;
    int16_t m_Ping = 0;
};

#endif // PACKETPLAYERLISTITEM_H

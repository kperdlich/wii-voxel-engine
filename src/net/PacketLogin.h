#ifndef PACKETLOGIN_H
#define PACKETLOGIN_H

#include <string>
#include "Packet.h"
#include "../globals.h"

class PacketLogin : public Packet
{
public:
    PacketLogin(const std::string playerName) : Packet(0x01), m_PlayerName(playerName) {}
protected:
    void SendContent(const Session& session) override
    {
        session.SendUInt((uint32_t)SERVER_PROTOCOL_VERSION);
        session.SendUShort((uint16_t)m_PlayerName.length());
        session.SendString(m_PlayerName);
        for(uint32_t i = 0; i < 13; ++i)
             session.SendByte(0x00);
    }
private:
    std::string m_PlayerName;
};

#endif // PACKETLOGIN_H

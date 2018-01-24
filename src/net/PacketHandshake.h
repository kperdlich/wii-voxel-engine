#ifndef PACKETHANDSHAKE_H
#define PACKETHANDSHAKE_H

#include "Packet.h"
#include <string>
#include "../utils/stringhelper.h"

class PacketHandshake : public Packet
{
public:
    PacketHandshake(std::string playerName, std::string ip, uint16_t port ) :
       m_PlayerName(playerName), m_IP(ip), m_Port(port), Packet(0x02) {}    
protected:

    void SendContent(const Session& session) override
    {
        std::string usernameAndHost;
        usernameAndHost.append(m_PlayerName);
        usernameAndHost+= ';';
        usernameAndHost.append(m_IP);
        usernameAndHost+= ':';
        usernameAndHost.append(ToString<uint16_t>(m_Port));

        session.SendUShort((uint16_t)usernameAndHost.length());
        session.SendString(usernameAndHost);
    }

private:
    std::string m_PlayerName;
    std::string m_IP;
    uint16_t m_Port;
};

#endif // PACKETHANDSHAKE_H

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

    void BuildPacket() override
    {
        uint32_t size = 0;
        std::string usernameAndHost;
        usernameAndHost.append(m_PlayerName);
        usernameAndHost+= ';';
        usernameAndHost.append(m_IP);
        usernameAndHost+= ':';
        usernameAndHost.append(ToString<uint16_t>(m_Port));

        uint16_t len = usernameAndHost.length();
        size = 1 + (len * 2) + sizeof(uint16_t);
        char* data = (char*) malloc(size);

        data[0] = m_ID;
        (*(uint16_t*)&data[1]) = len;

        WriteNetworkString(data, usernameAndHost.c_str(), len, 3);

        m_Data.Size = size;
        m_Data.Data = data;
    }

private:
    std::string m_PlayerName;
    std::string m_IP;
    uint16_t m_Port;
};

#endif // PACKETHANDSHAKE_H

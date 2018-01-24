#ifndef PACKETLOGIN_H
#define PACKETLOGIN_H

#include <string>
#include "Packet.h"
#include "../utils/stringhelper.h"

class PacketLogin : public Packet
{
public:
    PacketLogin(const std::string playerName) : Packet(0x01), m_PlayerName(playerName) {}
protected:
    void BuildPacket() override
    {
        uint32_t pos = 0, size = 0;
        uint16_t playerLen = m_PlayerName.length();

        size = 1 + sizeof(uint32_t) + sizeof(uint16_t) + (playerLen*2) + 13;
        char* data = (char*) malloc(size);

        data[pos++] = m_ID;
        (*(uint32_t*)&data[pos]) = 29;
        pos+= sizeof(uint32_t);

        (*(uint16_t*)&data[pos]) = playerLen;
        pos+= sizeof(uint16_t);

        pos += WriteNetworkString(data, m_PlayerName.c_str(), playerLen, pos);

        for(uint32_t i = 0; i < 13; ++i, ++pos)
            data[pos] = 0;

        m_Data.Size = size;
        m_Data.Data = data;
    }
private:
    std::string m_PlayerName;
};

#endif // PACKETLOGIN_H

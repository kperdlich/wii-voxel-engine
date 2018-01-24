#ifndef PACKETHANDSHAKE_H
/***
 *
 * Copyright (C) 2018 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#define PACKETHANDSHAKE_H

#include "Packet.h"
#include <string>
#include "../utils/stringhelper.h"

class PacketHandshake : public Packet
{
public:
    PacketHandshake(std::string playerName, std::string ip, uint16_t port ) :
       m_PlayerName(playerName), m_IP(ip), m_Port(port), Packet(PACKET_HANDSHAKE) {}
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

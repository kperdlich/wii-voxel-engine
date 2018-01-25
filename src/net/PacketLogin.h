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

#ifndef PACKETLOGIN_H
#define PACKETLOGIN_H

#include <string>
#include "Packet.h"
#include "../globals.h"

class PacketLogin : public Packet
{
public:
    PacketLogin(const std::string playerName) : Packet(PACKET_LOGIN), m_PlayerName(playerName) {}
protected:
    void SendContent(const Session& session) override
    {
        session.Send<int32_t>((int32_t)SERVER_PROTOCOL_VERSION);
        session.Send<int16_t>((int16_t)m_PlayerName.length());
        session.SendString(m_PlayerName);
        for(uint32_t i = 0; i < 13; ++i)
             session.Send<char>(0x00);
    }
private:
    std::string m_PlayerName;
};

#endif // PACKETLOGIN_H

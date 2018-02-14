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
#include "PacketGlobals.h"
#include "../../globals.h"

class PacketLogin : public Packet
{
public:
    PacketLogin() : Packet(PACKET_LOGIN) {}
    PacketLogin(const std::string playerName) : Packet(PACKET_LOGIN), m_PlayerName(playerName), m_ProtocolVersion(SERVER_PROTOCOL_VERSION) {}

    void Read(const Session &session) override
    {
        m_ProtocolVersion = session.Read<int32_t>();
        session.Read<int16_t>(); // read unused empty string
        m_LevelType     = session.ReadString();
        m_ServerMode    = session.Read<int32_t>();
        m_Dimension     = session.Read<int32_t>();
        m_Difficulty    = session.Read<char>();
        m_Vanilla       = session.Read<unsigned char>();
        m_MaxPlayers    = session.Read<unsigned char>();
    }

    void Action() override
    {
        // todo implement
    }

    Packet* CreateInstance() const override
    {
       return new PacketLogin();
    }

protected:
    void SendContent(const Session& session) const override
    {
        session.Send<int32_t>(m_ProtocolVersion);
        session.Send<int16_t>((int16_t)m_PlayerName.length());
        session.SendString(m_PlayerName);
        for(uint32_t i = 0; i < 13; ++i)
             session.Send<char>(0x00);
    }
private:
    int32_t m_ProtocolVersion;
    std::string m_PlayerName;
    std::string m_LevelType;
    int32_t m_ServerMode;
    int32_t m_Dimension;
    char m_Difficulty;
    unsigned char m_Vanilla;
    unsigned char m_MaxPlayers;
};

#endif // PACKETLOGIN_H

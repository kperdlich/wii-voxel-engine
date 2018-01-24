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

#include "Session.h"

bool Session::Connect(const std::string& ip, uint16_t port)
{
    m_IP = ip;
    m_Port = port;
    return m_Socket.Connect(m_IP, m_Port);
}

void Session::Close()
{
    m_Socket.Disconnect();
}

void Session::Update()
{
    // todo send keepAlive packet
}

void Session::SendInt(int32_t value) const
{
    m_Socket.Write((const char*)&value, sizeof(value));
}

void Session::SendByte(char byte) const
{
    m_Socket.Write(&byte, sizeof(byte));
}

void Session::SendShort(int16_t value) const
{
    m_Socket.Write((const char*)&value, sizeof(value));
}

void Session::SendString(const std::string &value) const
{
    for(uint32_t i = 0; i < value.length(); ++i)
    {
        SendByte(0x00);
        SendByte(value[i]);
    }
}

void Session::Send(const char *data, size_t size) const
{
    m_Socket.Write(data, size);
}

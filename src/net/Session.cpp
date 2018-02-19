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

void Session::SendString(const std::string &value) const
{
    for (uint32_t i = 0; i < value.length(); ++i)
    {
        Send<char>(0x00);
        Send<char>(value[i]);
    }
}

void Session::Send(const char *data, size_t size) const
{
    m_Socket.Write(data, size);
}

void Session::Read(void *data, size_t size) const
{
    m_Socket.Read(data, size);
}

std::string Session::ReadString() const
{
    std::string str;
    int16_t len = Read<int16_t>();
    for (int16_t i = 0; i < len; ++i)
    {
        Read<char>(); // 0x00
        str+=Read<char>();
    }
    return str;
}

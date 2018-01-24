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

#ifndef SOCKET_H
#define SOCKET_H

#include <string>

class Socket
{
public:
    ~Socket();
    bool Connect(const std::string& host, uint16_t port);
    void Disconnect();
    void Write(const char* data, size_t size) const;
    int32_t Read(void *data, size_t size) const;

    inline bool IsConnected() const
    {
        return m_bConnected;
    }

private:
    int32_t m_Socked;
    bool m_bConnected = false;
};

#endif // SOCKET_H

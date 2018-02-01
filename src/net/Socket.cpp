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

#include "Socket.h"
#include <network.h>
#include "../utils/Debug.h"

Socket::~Socket()
{
    Disconnect();
}

bool Socket::Connect(const std::string &host, uint16_t port)
{
    m_bConnected = false;

    m_Socket = net_socket (AF_INET, SOCK_STREAM, IPPROTO_IP);
    if ( m_Socket < 0)
    {
        ERROR("Failed creating socket!");
        return false;
    }

    struct sockaddr_in server;
    struct in_addr addr;

    inet_aton(host.c_str(), &addr);

    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_len = sizeof(struct sockaddr_in);
    memcpy((char*) &server.sin_addr, &addr.s_addr, sizeof(struct in_addr));

    int32_t bindingState = net_connect(m_Socket, (struct sockaddr*) &server, sizeof (server));
    if ( bindingState < 0)
    {
        ERROR("Socket failed to connect!");
        return false;
    }

    LOG("Socket connected to %s:%d", host.c_str(), port);
    m_bConnected = true;
    return true;
}

void Socket::Disconnect()
{
    if (m_bConnected)
    {
        m_bConnected = false;
        net_close(m_Socket);
        LOG("Socket closed connection!");
    }
}

void Socket::Write(const char* data, size_t size) const
{
    while(size > 0)
        size -= net_write(m_Socket, data, size);
}

int32_t Socket::Read(void* data, size_t size) const
{
    return net_read(m_Socket, data, size);
}

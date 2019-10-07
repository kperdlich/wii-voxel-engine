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

#pragma once

#include <map>
#include "net/Socket.h"
#include "utils/Thread.h"
#include "utils/SafeQueue.h"

class ServerConnection : public Thread
{
public:
    ServerConnection();
    ServerConnection(const ServerConnection&) = delete;
    ServerConnection(ServerConnection&&) = delete;
    void operator=(const ServerConnection&) = delete;
    void operator=(ServerConnection&&) = delete;

    bool Connect(const std::string& ip, uint16_t port);
    void Destroy();

    inline const Socket& GetSocket() const
    {
        return m_socket;
    }

    inline class Packet* PopPacket()
    {
        if (!m_queue.IsEmpty())
            return m_queue.Pop();
        return nullptr;
    }

private:
    static void DestroyPacketMap();
    static void InitPacketMap();
    static class Packet* CreatePacketByID(char id);
    void DestroyQueue();
protected:
    void Execute() override;
    void PreExecute() override;
private:
    Socket m_socket;
    SafeQueue<class Packet*> m_queue;
    static std::map<unsigned char, class Packet*> s_PacketMap;
};

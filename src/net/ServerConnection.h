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

#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <map>
#include "Session.h"
#include "../utils/Thread.h"
#include "../utils/SafeQueue.h"

class ServerConnection : public Thread
{
public:
    ServerConnection();
    bool Connect(const std::string& ip, uint16_t port);
    void Destroy();

    inline const Session& GetSession() const
    {
        return m_Session;
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
    Session m_Session;
    SafeQueue<class Packet*> m_queue;
    static std::map<unsigned char, class Packet*> s_PacketMap;
};

#endif // SERVERCONNECTION_H

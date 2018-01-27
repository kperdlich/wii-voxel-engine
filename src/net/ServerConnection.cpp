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

#include <string>
#include "ServerConnection.h"
#include "PacketGlobals.h"
#include "PacketKeepAlive.h"
#include "PacketHandshake.h"
#include "PacketLogin.h"

std::map<unsigned char, class Packet*> ServerConnection::s_PacketMap;

ServerConnection::ServerConnection()
{
    InitPacketMap();
}

void ServerConnection::InitPacketMap()
{
    if (!s_PacketMap.empty())
        return;

    // Register all s2c packets here:
    s_PacketMap[PACKET_KEEP_ALIVE] = new PacketKeepAlive();
    s_PacketMap[PACKET_HANDSHAKE] = new PacketHandshake();
    s_PacketMap[PACKET_LOGIN] = new PacketLogin();

}

void ServerConnection::DestroyPacketMap()
{
    for (auto it = s_PacketMap.begin(); it != s_PacketMap.end(); ++it)
        delete it->second;
    s_PacketMap.clear();
}

Packet* ServerConnection::CreatePacketByID(char id)
{
    auto it = s_PacketMap.find(id);
    if (it != s_PacketMap.end())
    {
        return it->second->CreateInstance();
    }

    return nullptr;
}

void ServerConnection::DestroyQueue()
{
    while(!m_queue.IsEmpty())
        delete m_queue.Pop();
}

bool ServerConnection::Connect(const std::string &ip, uint16_t port)
{
    if (m_Session.Connect(ip, port))
    {
        return Start() == 0;
    }
    return false;
}

void ServerConnection::Destroy()
{
    m_Session.Close();
    Stop();    
    DestroyPacketMap();
    DestroyQueue();
}

void ServerConnection::PreExecute()
{
    while(true)
    {
        if (IsStopped())
            break;
        else
            Execute();
    }
}

void ServerConnection::Execute()
{
    char packetID = m_Session.Read<char>();
    Packet* p = CreatePacketByID(packetID);
    if (p)
    {
        LOG("Parse packetID %d", packetID);
        p->Read(m_Session);
        m_queue.Push(p);
    }
    else
    {
        ERROR("Couldn't find or create instance of packetID %d. Stop Packet reader!", packetID);
        Suspend(); // todo remove when all packets are implemented
    }
}

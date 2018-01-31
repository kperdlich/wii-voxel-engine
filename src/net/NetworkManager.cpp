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

#include <network.h>
#include "NetworkManager.h"
#include "packet/PacketHandshake.h"
#include "../utils/Debug.h"
#include "../utils/Thread.h"
#include "../utils/SafeQueue.h"

void NetworkManager::Init()
{
    m_bInitialized = if_config(m_LocalIP, m_Gateway, m_Netmask, true, 5) >= 0;
    if (m_bInitialized)
    {
        LOG("Network configured, ip: %s, gw: %s, mask %s", m_LocalIP, m_Gateway, m_Netmask);
    }
    else
    {
        ERROR("Network configuration failed!");
    }
}

void NetworkManager::Connect(const std::string &ip, uint16_t port)
{
    if (m_bInitialized)
        m_ServerConnection.Connect(ip, port);
}

void NetworkManager::Destroy()
{
    if (m_bInitialized)
        m_ServerConnection.Destroy();
}

void NetworkManager::Update()
{
    if(!m_bInitialized)
        return;

    for(uint16_t i = 0; i < 5; ++i)
    {
        Packet* p = m_ServerConnection.PopPacket();
        if (p)
        {
            p->Action();
            delete p;
        }
    }
}

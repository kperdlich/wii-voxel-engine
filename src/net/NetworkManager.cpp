#include <network.h>
#include "NetworkManager.h"
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

#include "PacketHandshake.h"
#include "../utils/Debug.h"
#include "../utils/Thread.h"
#include "../utils/SafeQueue.h"

void NetworkManager::Init()
{
    m_bInitialized = if_config(m_LocalIP, m_Gateway, m_Netmask, true, 5) >= 0;
    if (m_bInitialized)
    {
        LOG("network configured, ip: %s, gw: %s, mask %s", m_LocalIP, m_Gateway, m_Netmask);        
    }
    else
    {
        LOG("network configuration failed!");
    }
}

void NetworkManager::Connect(const std::string &ip, uint16_t port)
{
    if (m_bInitialized)
        m_Session.Connect(ip, port);
}

void NetworkManager::Close()
{
    if (m_bInitialized)
        m_Session.Close();
}

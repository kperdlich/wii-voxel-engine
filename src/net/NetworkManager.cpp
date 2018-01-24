#include <network.h>
#include "NetworkManager.h"
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


void NetworkManager::Send(const PacketData &packet)
{
    if (m_bInitialized)
        m_Session.Send(packet.Data, packet.Size);
}

#include "Packet.h"
#include "NetworkManager.h"

void Packet::Send()
{
    BuildPacket();
    NetworkManager::Get().Send(m_Data);
    free(m_Data.Data);
    m_Data.Data = nullptr;
}

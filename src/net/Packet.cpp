#include "Packet.h"
#include "NetworkManager.h"

void Packet::Send()
{    
    const Session& session = NetworkManager::Get().GetSession();
    if(session.IsRunning())
    {
        session.SendByte(m_ID);
        SendContent(session);
    }
}

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Packet.h"
#include "Session.h"

class NetworkManager
{
private:
    NetworkManager(){}
public:
    void Init();
    void Connect(const std::string& ip, uint16_t port);
    void Close();

    static NetworkManager& Get()
    {
        static NetworkManager s_instance;
        return s_instance;
    }

    inline bool Initialized()
    {
        return m_bInitialized;
    }

    inline const Session& GetSession()
    {
        return m_Session;
    }

    NetworkManager(NetworkManager const&) = delete;
    void operator=(NetworkManager const&) = delete;

private:
    char m_LocalIP[16];
    char m_Gateway[16];
    char m_Netmask[16];
    bool m_bInitialized = false;

    Session m_Session;    
};

#endif // NETWORKMANAGER_H

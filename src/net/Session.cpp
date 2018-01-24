#include "Session.h"


bool Session::Connect(const std::string& ip, uint16_t port)
{
    m_IP = ip;
    m_Port = port;
    return m_Socket.Connect(m_IP, m_Port);
}

void Session::Close()
{
    m_Socket.Disconnect();
}

void Session::Update()
{
    // todo send keepAlive packet
}

void Session::Send(const char *data, size_t size)
{
    m_Socket.Write(data, size);
}

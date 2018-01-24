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

void Session::SendUInt(uint32_t value) const
{
    m_Socket.Write((const char*)&value, sizeof(uint32_t));
}

void Session::SendByte(char byte) const
{
    m_Socket.Write(&byte, 1);
}

void Session::SendUShort(uint16_t value) const
{
    m_Socket.Write((const char*)&value, sizeof(uint16_t));
}

void Session::SendString(const std::string &value) const
{
    for(uint32_t i = 0; i < value.length(); ++i)
    {
        SendByte(0x00);
        SendByte(value[i]);
    }
}

void Session::Send(const char *data, size_t size) const
{
    m_Socket.Write(data, size);
}

#ifndef SESSION_H
#define SESSION_H

#include <string>
#include "Socket.h"

class Session
{
public:
    Session(){}
    bool Connect(const std::string& ip, uint16_t port);
    void Close();
    void Update();

    void SendUInt(uint32_t value) const;
    void SendUShort(uint16_t value) const;
    void SendByte(char byte) const;
    void SendString(const std::string& value) const;
    void Send(const char* data, size_t size) const;

    inline bool IsRunning() const
    {
        return m_Socket.IsConnected();
    }

private:   
    Socket m_Socket;
    std::string m_IP;
    uint16_t m_Port;

};

#endif // SESSION_H

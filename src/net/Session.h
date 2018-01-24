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
    void Send(const char* data, size_t size);

private:
    Socket m_Socket;
    std::string m_IP;
    uint16_t m_Port;

};

#endif // SESSION_H

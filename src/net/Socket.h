#ifndef SOCKET_H
#define SOCKET_H

#include <string>

class Socket
{
public:
    ~Socket();
    bool Connect(const std::string& host, uint16_t port);
    void Disconnect();
    void Write(const char* data, size_t size) const;
    int32_t Read(void *data, size_t size) const;

    inline bool IsConnected() const
    {
        return m_bConnected;
    }

private:
    int32_t m_Socked;
    bool m_bConnected = false;
};

#endif // SOCKET_H

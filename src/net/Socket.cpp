#include "Socket.h"
#include <network.h>
#include "../utils/Debug.h"

Socket::~Socket()
{
    Disconnect();
}

bool Socket::Connect(const std::string &host, uint16_t port)
{
    m_bConnected = false;

    m_Socked = net_socket (AF_INET, SOCK_STREAM, IPPROTO_IP);
    if ( m_Socked < 0)
    {
        LOG("Failed creating socket!");
        return false;
    }

    struct sockaddr_in server;
    struct in_addr addr;

    inet_aton(host.c_str(), &addr);

    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_len = sizeof(struct sockaddr_in);
    memcpy((char*) &server.sin_addr, &addr.s_addr, sizeof(struct in_addr));

    s32 bindingState = net_connect(m_Socked, (struct sockaddr*) &server, sizeof (server));
    if ( bindingState < 0)
    {
        LOG("Socket failed to connect!");
        return false;
    }

    LOG("Socket connected!");
    m_bConnected = true;
    return true;
}

void Socket::Disconnect()
{
    if (m_bConnected)
    {
        net_close(m_Socked);
        LOG("Socket closed connection!");
    }
}

void Socket::Write(const char* data, size_t size) const
{
    while(size > 0)
        size -= net_write(m_Socked, data, size);
}

int32_t Socket::Read(void* data, size_t size) const
{
    return net_read(m_Socked, data, size);
}

#ifndef PACKET_H
#define PACKET_H

#include <cstdio>

struct PacketData
{
    char* Data;
    size_t Size;
};

class Packet
{
public:
    Packet(unsigned char id) : m_ID(id) {}
    virtual ~Packet() {}
    void Send();    

protected:
    virtual void BuildPacket() = 0;
    unsigned char m_ID;
    PacketData m_Data;
};

#endif // PACKET_H

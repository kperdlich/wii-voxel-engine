#ifndef PACKET_H
#define PACKET_H

#include <cstdio>
#include "Session.h"



class Packet
{
public:
    Packet(unsigned char id) : m_ID(id) {}
    virtual ~Packet() {}
    void Send();
protected:
    virtual void SendContent(const Session& session) = 0;
    unsigned char m_ID;

};

#endif // PACKET_H

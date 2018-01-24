#ifndef PACKETKEEPALIVE_H
#define PACKETKEEPALIVE_H

#include "Packet.h"
#include <assert.h>

class PacketKeepAlive : public Packet
{
public:
    PacketKeepAlive(int32_t id = 0) : Packet(0x00), m_ID(id) {}
protected:
    void BuildPacket() override
    {
         size_t size = 0;
         size = 1 + sizeof(int32_t);
         char* data = (char*) malloc(size);

         data[0] = m_ID;
         (*(int32_t*)&data[1]) = m_ID;

         m_Data.Size = size;
         m_Data.Data = data;
    }
private:
    int32_t m_ID = 0;
};

#endif // PACKETKEEPALIVE_H

#ifndef PACKETEXPLOSION_H
#define PACKETEXPLOSION_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketExplosion : public Packet
{
public:
     PacketExplosion() : Packet(PACKET_EXPLOSION) {}
     ~PacketExplosion()
     {
         if(m_Records)
             delete [] m_Records;
     }

     void Read(const Socket &socket) override
     {
         m_X = socket.Read<double>();
         m_Y = socket.Read<double>();
         m_Z = socket.Read<double>();
         m_Radius = socket.Read<float>();
         m_RecordCount = socket.Read<int32_t>();
         m_Records = new char[m_RecordCount * (sizeof(char) * 3)];
         socket.Read(m_Records, m_RecordCount * (sizeof(char) * 3));
     }

     void Action() override
     {
     }
     Packet *CreateInstance() const override
     {
         return new PacketExplosion();
     }

protected:
     void SendContent(const Socket &socket) const override
     {
     }

     double m_X = 0, m_Y = 0, m_Z = 0;
     float m_Radius = 0.0f;
     int32_t m_RecordCount = 0;
     void* m_Records = nullptr;
};

#endif // PACKETEXPLOSION_H

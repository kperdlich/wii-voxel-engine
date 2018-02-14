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
             free(m_Records);
     }

     void Read(const Session &session) override
     {
         m_X = session.Read<double>();
         m_Y = session.Read<double>();
         m_Z = session.Read<double>();
         m_Radius = session.Read<float>();
         m_RecordCount = session.Read<int32_t>();
         m_Records = malloc(m_RecordCount * (sizeof(char) * 3));
         session.Read(m_Records, m_RecordCount * (sizeof(char) * 3));
     }

     void Action() override
     {
     }
     Packet *CreateInstance() const override
     {
         return new PacketExplosion();
     }

protected:
     void SendContent(const Session &session) const override
     {
     }

     double m_X = 0, m_Y = 0, m_Z = 0;
     float m_Radius = 0.0f;
     int32_t m_RecordCount = 0;
     void* m_Records = nullptr;
};

#endif // PACKETEXPLOSION_H

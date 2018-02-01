#ifndef PACKETPLAYERPOSITION_H
#define PACKETPLAYERPOSITION_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayerPosition : public Packet
{
public:

   PacketPlayerPosition(double x, double y, double z, double stance, bool onGround) :
       m_X(x), m_Y(y), m_Z(z), m_Stance(stance), m_bOnGround(onGround), Packet(PACKET_PLAYER_POSITION) {}

   PacketPlayerPosition() : Packet(PACKET_PLAYER_POSITION) {}

   void Read(const Session &session) override
   {

   }
   void Action() const override
   {

   }
   Packet *CreateInstance() const override
   {
        return new PacketPlayerPosition();
   }

protected:
   void SendContent(const Session &session) const override
   {
        session.Send<double>(m_X);
        session.Send<double>(m_Y);
        session.Send<double>(m_Stance);
        session.Send<double>(m_Z);
        session.Send<bool>(m_bOnGround);
   }

   double m_X, m_Y, m_Z, m_Stance;
   bool m_bOnGround = false;
};

#endif // PACKETPLAYERPOSITION_H

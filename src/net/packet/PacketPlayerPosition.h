#ifndef PACKETPLAYERPOSITION_H
#define PACKETPLAYERPOSITION_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketPlayerPosition : public Packet
{
public:
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

   }
};

#endif // PACKETPLAYERPOSITION_H

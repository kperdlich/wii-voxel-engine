#ifndef PACKETUSEENTITY_H
#define PACKETUSEENTITY_H

#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketUseEntity : public Packet
{
public:
     PacketUseEntity() : Packet(PACKET_USE_ENTITY) {}

     void Read(const Session &session) override
     {

     }
     void Action() override
     {

     }
     Packet *CreateInstance() const override
     {
        return new PacketUseEntity();
     }

protected:
     void SendContent(const Session &session) const override
     {

     }
};

#endif // PACKETUSEENTITY_H

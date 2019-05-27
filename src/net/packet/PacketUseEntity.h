#pragma once
#include "Packet.h"
#include "PacketGlobals.h"

// todo implement

class PacketUseEntity : public Packet
{
public:
     PacketUseEntity() : Packet(PACKET_USE_ENTITY) {}

     void Read(const Socket &socket) override
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
     void SendContent(const Socket &socket) const override
     {

     }
};

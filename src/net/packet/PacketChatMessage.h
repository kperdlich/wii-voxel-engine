#pragma once

#include "Packet.h"
#include "PacketGlobals.h"

class PacketChatMessage : public Packet
{
public:
     PacketChatMessage() : Packet(PACKET_CHAT_MESSAGE) {}

     void Read(const Socket &socket) override
     {
        m_chatMessage = socket.ReadString();
     }

     void Action() override
     {
        // todo implement
     }

     Packet *CreateInstance() const override
     {
        return new PacketChatMessage();
     }

protected:
     std::string m_chatMessage;
     void SendContent(const Socket &socket) const override
     {
         // todo implement
     }
};

#ifndef PACKETCHATMESSAGE_H
#define PACKETCHATMESSAGE_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketChatMessage : public Packet
{
public:
     PacketChatMessage() : Packet(PACKET_CHAT_MESSAGE) {}

     void Read(const Session &session) override
     {
        m_chatMessage = session.ReadString();
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
     void SendContent(const Session &session) const override
     {
         // todo implement
     }
};

#endif // PACKETCHATMESSAGE_H

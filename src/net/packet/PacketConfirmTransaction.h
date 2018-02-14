#ifndef PACKETCONFIRMTRANSACTION_H
#define PACKETCONFIRMTRANSACTION_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketConfirmTransaction : public Packet
{
public:
     PacketConfirmTransaction() : Packet(PACKET_CONFIRM_TRANSACTION) {}

     void Read(const Session &session) override
     {
         m_WindowID = session.Read<char>();
         m_ActionNumber = session.Read<uint16_t>();
         m_bAccepted = session.Read<bool>();
     }
     void Action() override
     {
     }
     Packet *CreateInstance() const override
     {
         return new PacketConfirmTransaction();
     }

protected:
     void SendContent(const Session &session) const override
     {
     }

     char m_WindowID = 0;
     uint16_t m_ActionNumber = 0;
     bool m_bAccepted = false;
};

#endif // PACKETCONFIRMTRANSACTION_H

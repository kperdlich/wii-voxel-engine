#ifndef PACKETOPENWINDOW_H
#define PACKETOPENWINDOW_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketOpenWindow : public Packet
{
public:
    PacketOpenWindow() : Packet(PACKET_OPEN_WINDOW) {}

    void Read(const Session &session) override
    {
        m_WindowID = session.Read<char>();
        m_InventoryType = session.Read<char>();
        m_WindowTitle = session.ReadString();
        m_NumberOfSlots = session.Read<char>();
    }

    void Action() const override
    {
    }

    Packet *CreateInstance() const override
    {
        return new PacketOpenWindow();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    char m_WindowID = 0, m_InventoryType = 0;
    std::string m_WindowTitle;
    char m_NumberOfSlots = 0;
};

#endif // PACKETOPENWINDOW_H

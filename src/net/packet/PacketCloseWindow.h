#ifndef PACKETCLOSEWINDOW_H
#define PACKETCLOSEWINDOW_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketCloseWindow : public Packet
{
public:
    PacketCloseWindow() : Packet(PACKET_CLOSE_WINDOW) {}

    void Read(const Session &session) override
    {
        m_WindowID = session.Read<char>();
    }

    void Action() const override
    {
    }

    Packet *CreateInstance() const override
    {
        return new PacketCloseWindow();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    char m_WindowID = 0;
};

#endif // PACKETCLOSEWINDOW_H

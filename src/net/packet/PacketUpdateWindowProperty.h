#ifndef PACKETUPDATEWINDOWPROPERTY_H
#define PACKETUPDATEWINDOWPROPERTY_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketUpdateWindowProperty : public Packet
{
public:
    PacketUpdateWindowProperty() : Packet(PACKET_UPDATE_WINDOW_PROPERTY) {}

    void Read(const Socket &socket) override
    {
        m_WindowID = socket.Read<char>();
        m_Property = socket.Read<int16_t>();
        m_Value = socket.Read<int16_t>();
    }
    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketUpdateWindowProperty();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
    }

    char m_WindowID = 0;
    int16_t m_Property = 0, m_Value = 0;

};

#endif // PACKETUPDATEWINDOWPROPERTY_H

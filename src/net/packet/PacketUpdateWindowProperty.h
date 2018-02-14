#ifndef PACKETUPDATEWINDOWPROPERTY_H
#define PACKETUPDATEWINDOWPROPERTY_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketUpdateWindowProperty : public Packet
{
public:
    PacketUpdateWindowProperty() : Packet(PACKET_UPDATE_WINDOW_PROPERTY) {}

    void Read(const Session &session) override
    {
        m_WindowID = session.Read<char>();
        m_Property = session.Read<int16_t>();
        m_Value = session.Read<int16_t>();
    }
    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketUpdateWindowProperty();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    char m_WindowID = 0;
    int16_t m_Property = 0, m_Value = 0;

};

#endif // PACKETUPDATEWINDOWPROPERTY_H

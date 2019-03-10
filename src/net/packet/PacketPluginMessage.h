#ifndef PACKETPLUGINMESSAGE_H
#define PACKETPLUGINMESSAGE_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketPluginMessage : public Packet
{
public:
    PacketPluginMessage() : Packet(PACKET_PLUGIN_MESSAGE) {}

    ~PacketPluginMessage()
    {
        if(m_Data)
            delete [] m_Data;
    }

    void Read(const Socket &socket) override
    {
        m_Channel = socket.ReadString();
        m_Length = socket.Read<int16_t>();
        m_Data = new char[m_Length];
        socket.Read(m_Data, m_Length);
    }
    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketPluginMessage();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
    }

    std::string m_Channel;
    int16_t m_Length = 0;
    void* m_Data = nullptr;
};

#endif // PACKETPLUGINMESSAGE_H

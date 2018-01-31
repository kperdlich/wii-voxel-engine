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
            free(m_Data);
    }

    void Read(const Session &session) override
    {
        m_Channel = session.ReadString();
        m_Length = session.Read<int16_t>();
        m_Data = malloc(m_Length);
        session.Read(m_Data, m_Length);
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketPluginMessage();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    std::string m_Channel;
    int16_t m_Length = 0;
    void* m_Data = nullptr;
};

#endif // PACKETPLUGINMESSAGE_H

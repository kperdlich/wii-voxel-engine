#ifndef PACKETITEMDATA_H
#define PACKETITEMDATA_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketItemData : public Packet
{
public:
    PacketItemData() : Packet(PACKET_ITEM_DATA) {}

    ~PacketItemData()
    {
        if (m_Text)
            free(m_Text);
    }

    void Read(const Session &session) override
    {
        m_ItemType = session.Read<int16_t>();
        m_ItemID = session.Read<int16_t>();
        m_TextLength = session.Read<unsigned char>();
        m_Text = (char*) malloc(m_TextLength);
        session.Read(m_Text, m_TextLength);
    }

    void Action() override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketItemData();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int16_t m_ItemType = 0, m_ItemID = 0;
    unsigned char m_TextLength = 0;
    char* m_Text = nullptr;
};

#endif // PACKETITEMDATA_H

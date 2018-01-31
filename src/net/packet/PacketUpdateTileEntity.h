#ifndef PACKETUPDATETILEENTITY_H
#define PACKETUPDATETILEENTITY_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketUpdateTileEntity : public Packet
{
public:
    PacketUpdateTileEntity() : Packet(PACKET_UPDATE_TILE_ENTITY) {}

    void Read(const Session &session) override
    {
        m_X = session.Read<int32_t>();
        m_Y = session.Read<int16_t>();
        m_Z = session.Read<int32_t>();
        m_Action= session.Read<char>();
        m_Custom1 = session.Read<int32_t>();
        m_Custom2 = session.Read<int32_t>();
        m_Custom3 = session.Read<int32_t>();
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketUpdateTileEntity();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_X = 0, m_Z = 0;
    int16_t m_Y = 0;
    char m_Action = 0;
    int32_t m_Custom1 = 0, m_Custom2 = 0, m_Custom3 = 0;
};

#endif // PACKETUPDATETILEENTITY_H

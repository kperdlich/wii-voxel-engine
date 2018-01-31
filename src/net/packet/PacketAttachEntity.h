#ifndef PACKETATTACHENTITY_H
#define PACKETATTACHENTITY_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketAttachEntity : public Packet
{
public:
    PacketAttachEntity() : Packet(PACKET_ATTACH_ENTITY) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        m_VehicleID = session.Read<int32_t>();
    }

    void Action() const override
    {
    }
    Packet* CreateInstance() const override
    {
        return new PacketAttachEntity();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0, m_VehicleID = 0;
};

#endif // PACKETATTACHENTITY_H

#ifndef PACKETENTITYMETADATA_H
#define PACKETENTITYMETADATA_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketEntityMetadata : public Packet
{
public:
    PacketEntityMetadata() : Packet(PACKET_ENTITY_METADATA) {}

    void Read(const Session &session) override
    {
        m_EID = session.Read<int32_t>();
        // todo implement metadata
    }
    void Action() const override
    {
    }
    Packet *CreateInstance() const override
    {
        return new PacketEntityMetadata();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_EID = 0;

};

#endif // PACKETENTITYMETADATA_H

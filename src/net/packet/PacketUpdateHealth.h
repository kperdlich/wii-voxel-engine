#ifndef PACKETUPDATEHEALTH_H
#define PACKETUPDATEHEALTH_H

#include "Packet.h"
#include "PacketGlobals.h"

class PacketUpdateHealth : public Packet
{
public:
    PacketUpdateHealth() : Packet(PACKET_UPDATE_HEALTH) {}

    void Read(const Session &session) override
    {
        m_Health = session.Read<int16_t>();
        m_Food = session.Read<int16_t>();
        m_FoodSaturation = session.Read<float>();
    }
    void Action() const override
    {

    }
    Packet *CreateInstance() const override
    {
        return new PacketUpdateHealth();
    }

protected:
    int16_t m_Health = 0, m_Food = 0;
    float m_FoodSaturation = 0.0f;

    void SendContent(const Session &session) const override
    {

    }
};

#endif // PACKETUPDATEHEALTH_H

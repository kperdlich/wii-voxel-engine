#ifndef PACKETCHUNKALLOCATION_H
#define PACKETCHUNKALLOCATION_H

#include "Packet.h"
#include "PacketGlobals.h"
#include "../../scenes/InGameScene.h"
#include "../../world/GameWorld.h"
#include "../../world/chunk/Chunk.h"

class PacketChunkAllocation : public Packet
{
public:
    PacketChunkAllocation() : Packet(PACKET_CHUNK_ALLOCATION) {}

    void Read(const Session& session) override
    {
        m_x     =   session.Read<int32_t>();
        m_y     =   session.Read<int32_t>();
        m_bMode =   session.Read<bool>();
    }

    void Action() override
    {
        GameWorld* world = dynamic_cast<InGameScene*>(Engine::Get().GetSceneHandler().GetCurrentScene())->GetWorld();
        if (world)
        {
            LOG("Allocate chunk %d, %d Mode:%d", m_x, m_y, m_bMode);

            /*Chunk* c = world->GetCashedChunkByWorldPosition(Vector3((double)(m_x * CHUNK_SIZE_X), CHUNK_BLOCK_SIZE_Y / 2, (double) (m_y * CHUNK_SIZE_Z)));
            if(c)
            {
                LOG("Found chunk for X:%d; Y:%d; Chunk: X:%f Y:%f Z:%f", m_x, m_y,
                        c->GetCenterPosition().GetX(), c->GetCenterPosition().GetY(), c->GetCenterPosition().GetZ());
            }*/
        }
        else
        {
            ERROR("World is not initialized");
        }
    }

    Packet *CreateInstance() const override
    {
        return new PacketChunkAllocation();
    }

protected:
    void SendContent(const Session &session) const override {}
    int32_t m_x = 0, m_y = 0;
    bool m_bMode = false;
};

#endif // PACKETCHUNKALLOCATION_H

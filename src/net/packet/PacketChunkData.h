#ifndef PACKETCHUNKDATA_H
#define PACKETCHUNKDATA_H

#include "Packet.h"
#include "PacketGlobals.h"
#include "../../utils/Zip.h"
#include "../../utils/Debug.h"
#include "../../utils/Vector3.h"
#include "../../Engine.h"
#include "../../scenes/InGameScene.h"
#include "../../world/GameWorld.h"
#include "../../world/chunk/Chunk.h"

// todo implement

class PacketChunkData : public Packet
{
public:
    PacketChunkData() : Packet(PACKET_CHUNK_DATA) {}
    ~PacketChunkData()
    {
        if (m_CompressedData)
            free(m_CompressedData);

    }

    void Read(const Session &session) override
    {
        m_X = session.Read<int32_t>();
        m_Z = session.Read<int32_t>();
        m_bGroundUpCon = session.Read<bool>();
        m_PrimaryBitMap = session.Read<uint16_t>();
        m_AddBitMap = session.Read<uint16_t>();
        m_CompressedSize = session.Read<int32_t>();
        m_UnusedInt = session.Read<int32_t>();
        m_CompressedData = (unsigned char*) malloc(m_CompressedSize);
        session.Read(m_CompressedData, m_CompressedSize);
    }

    void Action() override
    {
        int32_t sections = 0;
        const int32_t sectionSize = 4096+(3*2048);

        for(uint32_t i = 0; i < 16; ++i)
            sections += m_PrimaryBitMap >> i & 1;

        size_t size = sections * sectionSize;
        if(m_bGroundUpCon)
            size += 256;

        unsigned char* cdata = Zip::Decompress(m_CompressedData, m_CompressedSize, size);
        free(m_CompressedData);
        m_CompressedData = nullptr;

        LOG("Chunk Data X:%d Z:%d m_bGroundUpCon:%d, m_PrimaryBitMap:%d, m_AddBitMap:%d, m_CompressedSize:%d, ", m_X, m_Z, m_bGroundUpCon, m_PrimaryBitMap,
            m_AddBitMap, m_CompressedSize);

        GameWorld* world = static_cast<InGameScene*>(Engine::Get().GetSceneHandler().GetCurrentScene())->GetWorld();
        Chunk* c = world->GetCashedChunkAt(Vec2i(m_X, m_Z));

        if(c)
        {
            BlockType*** blocks = c->GetBlocks();
            uint32_t index = 0;

            for (uint32_t i = 0; i < 16; i++)
            {
                if (m_PrimaryBitMap & 1 << i)
                {
                    for (uint32_t x = 0; x < 16; x++)
                    {
                        for (uint32_t y = 0; y < 16; y++)
                        {
                            for (uint32_t z = 0; z < 16; z++)
                            {
                                blocks[x][y*i][z] = BlockType(cdata[index++]);
                            }
                        }
                    }
                }
            }
            c->SetDirty(true);
        }

        free(cdata);
    }

    Packet *CreateInstance() const override
    {
        return new PacketChunkData();
    }

protected:
    void SendContent(const Session &session) const override
    {
    }

    int32_t m_X = 0, m_Z = 0;
    bool m_bGroundUpCon = false;
    uint16_t m_PrimaryBitMap = 0, m_AddBitMap = 0;
    int32_t m_CompressedSize = 0, m_UnusedInt = 0;
    unsigned char* m_CompressedData = nullptr;


};

#endif // PACKETCHUNKDATA_H

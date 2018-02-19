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
        uint32_t sections = 0;
        const int32_t sectionSize = 4096+(4*2048);

        for(uint32_t i = 0; i < 16; ++i)
            sections += m_PrimaryBitMap >> i & 1;

        size_t size = sections * sectionSize;
        if(m_bGroundUpCon)
            size += 256;

        unsigned char* cdata = Zip::Decompress(m_CompressedData, m_CompressedSize, size);
        free(m_CompressedData);
        m_CompressedData = nullptr;      

        GameWorld* world = static_cast<InGameScene*>(Engine::Get().GetSceneHandler().GetCurrentScene())->GetWorld();
        Chunk* c = world->GetCashedChunkAt(Vec2i(m_X, m_Z));

        if(c)
        {
            /*LOG("Found Chunk Data X:%d Z:%d m_bGroundUpCon:%d, m_PrimaryBitMap:%d, m_AddBitMap:%d, m_CompressedSize:%d, ", m_X, m_Z, m_bGroundUpCon, m_PrimaryBitMap,
                m_AddBitMap, m_CompressedSize);*/

            c->SetToAir();
            BlockType*** blocks = c->GetBlocks();

            for (uint32_t i = 0; i < sections; ++i)
            {
                if (m_PrimaryBitMap & 1 << i)
                {                    
                    for(int j = 0; j < 4096; ++j)
                    {
                        int32_t x = j & 0x0F;
                        int32_t y = i*16 + j >> 8;
                        int32_t z = (j & 0xF0) >> 4;
                        unsigned char data = cdata[j];
                        blocks[x][y][z] = data > 5 ? BlockType::DIRT : BlockType(data);
                    }
                }               
            }
            c->SetDirty(true);
        }
        else
        {
            ERROR("Couldn't find Chunk Data X:%d Z:%d", m_X, m_Z);
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

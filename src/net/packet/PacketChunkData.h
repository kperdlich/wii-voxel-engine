#ifndef PACKETCHUNKDATA_H
#define PACKETCHUNKDATA_H

#include <iostream>
#include <stdlib.h>
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

    void Read(const Socket &socket) override
    {
        m_X = socket.Read<int32_t>();
        m_Z = socket.Read<int32_t>();
        m_bGroundUpCon = socket.Read<bool>();
        m_PrimaryBitMap = socket.Read<uint16_t>();
        m_AddBitMap = socket.Read<uint16_t>();
        m_CompressedSize = socket.Read<int32_t>();
        m_UnusedInt = socket.Read<int32_t>();
        m_CompressedData = (unsigned char*) malloc(m_CompressedSize);
        socket.Read(m_CompressedData, m_CompressedSize);
    }

    void Action() override
    {
        /*std::ofstream stream(Chunk::GetFilePath(Vec2i(m_X, m_Z)), std::ios::out | std::ios::binary);
        stream.write((const char*)&m_X, sizeof(m_X));
        stream.write((const char*)&m_Z, sizeof(m_Z));
        stream.write((const char*)&m_bGroundUpCon, sizeof(m_bGroundUpCon));
        stream.write((const char*)&m_PrimaryBitMap, sizeof(m_PrimaryBitMap));
        stream.write((const char*)&m_AddBitMap, sizeof(m_AddBitMap));
        stream.write((const char*)&m_CompressedSize, sizeof(m_CompressedSize));
        stream.write((const char*)&m_UnusedInt, sizeof(m_UnusedInt));
        stream.write((const char*)m_CompressedData, m_CompressedSize);
        stream.flush();
        stream.close();*/

        //return; // TODO REMOVE WHEN IMPLEMENTED SECTION DISPLAY LIST

        uint32_t sections = 0;
        const int32_t sectionSize = 4096+(3*2048);

        for(uint32_t i = 0; i < 16; ++i)
            sections += m_PrimaryBitMap >> i & 1;

        size_t size = sections * sectionSize;
        if(m_bGroundUpCon)
            size += 256;

        /*LOG("Received Chunk Data X:%d Z:%d m_bGroundUpCon:%d, m_PrimaryBitMap:%d, m_AddBitMap:%d, m_CompressedSize:%d, ", m_X, m_Z, m_bGroundUpCon, m_PrimaryBitMap,
                        m_AddBitMap, m_CompressedSize);*/

        unsigned char* cdata = (unsigned char*) malloc(size);
        size_t s = Zip::Decompress(m_CompressedData, m_CompressedSize, cdata, size);
        if (s != size)
            ERROR("Uncompressed size is different: Got: %d, Expected: %d", s, size);

        free(m_CompressedData);
        m_CompressedData = nullptr;

        GameWorld* world = static_cast<InGameScene*>(Engine::Get().GetSceneHandler().GetCurrentScene())->GetWorld();
        Chunk* c = world->GetCashedChunkAt(Vec2i(m_X, m_Z));
        if(c)
        {
            LOG("Receiced cashed Chunk Data X:%d Z:%d m_bGroundUpCon:%d, m_PrimaryBitMap:%d, m_AddBitMap:%d, m_CompressedSize:%d, ", m_X, m_Z, m_bGroundUpCon, m_PrimaryBitMap,
                                    m_AddBitMap, m_CompressedSize);
            // TODO create sections in chunk first before working more on parsing the shit ..
            BlockType*** blocks = c->GetBlocks();
            for (uint32_t i = 0; i < 8; ++i) // todo change to 16
            {
                if (m_PrimaryBitMap & 1 << i)
                {
                    for (int ix = 0; ix < 16; ++ix)
                    {
                        for (int iy = 0; iy < 16; ++iy)
                        {
                            for (int iz = 0; iz < 16; ++iz)
                            {
                                unsigned char block = (cdata[(iz * 16 * 16) + (iy * 16) + ix + (i * 16 * 16 * 16)]);
                                BlockType* blockPtr = &blocks[ix][ iz + (i * 16)][iy];

                                switch(block)
                                {
                                case 0:
                                    *blockPtr = BlockType::AIR;
                                    break;
                                case 2:
                                    *blockPtr = BlockType::GRASS;
                                    break;
                                case 3:
                                    *blockPtr = BlockType::DIRT;
                                    break;
                                case 4:
                                    *blockPtr = BlockType::STONE;
                                    break;
                                case 5:
                                    *blockPtr = BlockType::WOOD;
                                    break;
                                case 17:
                                    *blockPtr = BlockType::WOOD;
                                    break;
                                case 18:
                                    *blockPtr = BlockType::LEAF;
                                    break;
                                default:
                                    *blockPtr = BlockType::DIRT;
                                    break;
                                }
                            }
                        }
                    }
                    c->SetDirty(true);
                    c->SetLoaded(true);
                    c->RebuildDisplayList();
                }
            }
        }

        free(cdata);
        LOG("DONE Parsing chunk");
    }

    Packet *CreateInstance() const override
    {
        return new PacketChunkData();
    }

protected:
    void SendContent(const Socket &socket) const override
    {
    }

    int32_t m_X = 0, m_Z = 0;
    bool m_bGroundUpCon = false;
    uint16_t m_PrimaryBitMap = 0, m_AddBitMap = 0;
    int32_t m_CompressedSize = 0, m_UnusedInt = 0;
    unsigned char* m_CompressedData = nullptr;


};

#endif // PACKETCHUNKDATA_H

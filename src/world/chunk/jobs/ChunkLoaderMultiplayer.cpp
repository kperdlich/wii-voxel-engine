
#include <iostream>
#include <sstream>
#include "ChunkLoaderMultiplayer.h"
#include "../Chunk.h"
#include "../chunkdata.h"
#include "../../../utils/Zip.h"
#include "../../../utils/Clock.h"

void ChunkLoaderMultiplayer::Execute()
{
    Clock clock;
    clock.Start();
    const ChunkLoadingData& chunkData = m_queue.Pop();
    Chunk* chunk = chunkData.ChunkObj;

    std::ostringstream filename;
    filename << WORLD_PATH "/";
    filename << chunk->GetPosition().X;
    filename << '_';
    filename << chunk->GetPosition().Y;
    filename << ".data";

    //LOG("Try load chunk %s", filename.str().c_str());

    std::ifstream fstream(filename.str(), std::ios::in | std::ios::binary);    
    if (fstream)
    {
        int32_t x = 0, z = 0;
        bool bGroundUpCon = false;
        uint16_t primaryBitMap = 0, addBitMap = 0;
        int32_t compressedSize = 0;
        unsigned char* compressedData = nullptr;

        fstream.read((char*)&x, sizeof(x));
        fstream.read((char*)&z, sizeof(z));
        fstream.read((char*)&bGroundUpCon, sizeof(bGroundUpCon));
        fstream.read((char*)&primaryBitMap, sizeof(primaryBitMap));
        fstream.read((char*)&addBitMap, sizeof(addBitMap));
        fstream.read((char*)&compressedSize, sizeof(compressedSize));
        compressedData = new unsigned char[compressedSize];
        fstream.read((char*)compressedData, compressedSize);
        fstream.close();

        uint32_t sections = 0;
        const int32_t sectionSize = 4096+(3*2048);

        for(uint32_t i = 0; i < 16; ++i)
            sections += primaryBitMap >> i & 1;

        size_t size = sections * sectionSize;
        if(bGroundUpCon)
            size += 256;

        unsigned char* cdata = new unsigned char[size];
        size_t s = Zip::Decompress(compressedData, compressedSize, cdata, size);
        if (s != size)
        {
            ERROR("Uncompressed size is different: Got: %d, Expected: %d, Chunk: %d %d, CompressedSize: %d, primaryBitMap: %d",
                  s, size, x, z, compressedSize, primaryBitMap);
            delete [] compressedData;
            delete [] cdata;
            return;
        }

        delete [] compressedData;
        compressedData = nullptr;

        BlockType*** blocks = chunk->GetBlocks();
        for (uint32_t i = 0; i < 16; ++i)
        {
            if (primaryBitMap & 1 << i)
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
                            case 1:
                                *blockPtr = BlockType::STONE;
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
                            case 31:
                                *blockPtr = BlockType::AIR;
                                break;
                            default:
                                *blockPtr = BlockType::DIRT;
                                break;
                            }
                        }
                    }
                }
                chunk->SetDirty(true);
                chunk->SetLoaded(true);
                //chunk->RebuildDisplayList();
            }
        }
        delete [] cdata;
        clock.Stop();
        //LOG("ChunkLoader took %fs to load %d %d", clock.GetSecs(), chunk->GetPosition().X, chunk->GetPosition().Y);
    }
    else
    {
        WARNING("Found no chunk file for %d %d", chunk->GetPosition().X, chunk->GetPosition().Y);
    }    
}

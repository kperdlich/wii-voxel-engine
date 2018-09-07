
#include <iostream>
#include "ChunkLoaderMultiplayer.h"
#include "../Chunk.h"
#include "../chunkdata.h"
#include "../../../utils/Zip.h"

void ChunkLoaderMultiplayer::Execute()
{
    const ChunkLoadingData& chunkData = m_queue.Pop();
    Chunk* chunk = chunkData.ChunkObj;
    const std::string& filepath = chunkData.Filepath;

    std::ifstream fstream(filepath, std::ios::in | std::ios::binary);
    if (fstream.is_open())
    {
        int32_t x = 0, z = 0;
        bool bGroundUpCon = false;
        uint16_t primaryBitMap = 0, addBitMap = 0;
        int32_t compressedSize = 0, unusedInt = 0;
        unsigned char* compressedData = nullptr;

        fstream.read((char*)&x, sizeof(x));
        fstream.read((char*)&z, sizeof(z));
        fstream.read((char*)&bGroundUpCon, sizeof(bGroundUpCon));
        fstream.read((char*)&primaryBitMap, sizeof(primaryBitMap));
        fstream.read((char*)&addBitMap, sizeof(addBitMap));
        fstream.read((char*)&compressedSize, sizeof(compressedSize));
        fstream.read((char*)&unusedInt, sizeof(unusedInt));

        compressedData = (unsigned char*) malloc(compressedSize);
        fstream.read((char*) compressedData, compressedSize);

        fstream.close();

        uint32_t sections = 0;
        const int32_t sectionSize = 4096+(3*2048);

        for(uint32_t i = 0; i < 16; ++i)
            sections += primaryBitMap >> i & 1;

        size_t size = sections * sectionSize;
        if (bGroundUpCon)
            size += 256;

        unsigned char* cdata = (unsigned char*) malloc(size);
        size_t s = Zip::Decompress(compressedData, compressedSize, cdata, size);
        if (s != size)
            ERROR("Uncompressed size is different: Got: %d, Expected: %d", s, size);

        free(compressedData);
        compressedData = nullptr;

        BlockType*** blocks = chunk->GetBlocks();
        chunk->SetToAir();
        for (uint32_t i = 0; i < 16; ++i)
        {
            if (primaryBitMap & 1 << i)
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
        chunk->SetLoaded(true);
        free(cdata);
    }
    else
    {
        ERROR("Couldn find file: %s", filepath.c_str());
    }
}

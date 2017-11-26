/***
 *
 * Copyright (C) 2017 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Chunkserializer.h"
#include "../../utils/Filesystem.h"
#include "../../utils/threadpool.h"
#include "../../utils/Debug.h"

void* SerializeChunkData(void* data);

ChunkSerializer::ChunkSerializer() {}

ChunkSerializer::~ChunkSerializer()
{
    /*if (!m_bInitalized)
        return;

    for (auto& chunk : m_serializeChunkCash)
    {
        auto blockData = chunk.BlockData;

        for (int x = 0; x < CHUNK_SIZE_X; ++x)
        {
            for (int y = 0; y < CHUNK_SIZE_Y; ++y)
            {
                delete [] blockData[x][y];
            }

            delete [] blockData[x];
        }
        delete [] blockData;
    }*/
}

void ChunkSerializer::Init()
{
    /*LWP_MutexInit(&s_mutex, false);
    for ( uint32_t i = 0; i < 14; i++)
    {
        BlockType*** blockData = new BlockType**[CHUNK_SIZE_X]();
        for (uint32_t x = 0; x < CHUNK_SIZE_X; x++)
        {
            blockData[x] = new BlockType*[CHUNK_SIZE_Y]();
            for (uint32_t y = 0; y < CHUNK_SIZE_Y; y++)
            {
                blockData[x][y] = new BlockType[CHUNK_SIZE_Z]();
            }
        }
        m_serializeChunkCash.emplace_back( ChunkSerializeData{ blockData } );
    }

    m_bInitalized = true;*/
}

void ChunkSerializer::Serialize(const Chunk &chunk, const BlockChangeData* data)
{
    Thread* thread = ThreadPool::GetThread();
    if ( thread )
    {
        thread->Data = (void*)data;
        thread->Create( SerializeChunkData, nullptr, 0, 120);
    }
    else
    {
        LOG("No free thread in pool");
    }
}

void ChunkSerializer::Deserialize(const std::string &filepath, Chunk *chunk)
{
    // todo fill chunk from file
    Vector3 chunkCenterPos;
    std::ifstream fstream;
    fstream.open(filepath);
    if (fstream.is_open())
    {
        chunk->Clear();
        std::string line;
        if (fstream.good())
        {
            std::getline(fstream, line, ';');
            chunkCenterPos.SetX(std::atof(line.c_str()));
            std::getline(fstream, line, ';');
            chunkCenterPos.SetY(std::atof(line.c_str()));
            std::getline(fstream, line);
            chunkCenterPos.SetZ(std::atof(line.c_str()));

            LOG("Header %f %f %f", chunkCenterPos.GetX(), chunkCenterPos.GetY(), chunkCenterPos.GetZ());
            chunk->Init(chunkCenterPos);
        }

        auto blocks = chunk->GetBlocks();
        size_t posX, posY, posZ, posValue;
        while (std::getline(fstream, line))
        {
            posX        = line.find("X");
            posY        = line.find("Y");
            posZ        = line.find("Z");
            posValue    = line.find(":");

            uint32_t x      = std::atoi(line.substr(posX+1, posY - posX).c_str());
            uint32_t y      = std::atoi(line.substr(posY+1, posZ - posY).c_str());
            uint32_t z      = std::atoi(line.substr(posZ+1, posValue - posZ).c_str());
            uint32_t value  = std::atoi(line.substr(posValue+1).c_str());

            blocks[x][y][z] = value;

            LOG("Line %s", line.c_str());
            LOG("Line %d %d %d %d", x, y, z, value);
        }

        chunk->SetDirty(true);
    }

    fstream.close();
}


void* SerializeChunkData(void* data)
{
    auto thread = static_cast<Thread*>(data);
    auto blockData = static_cast<const BlockChangeData*>(thread->Data);

    std::ostringstream filename;
    filename << "World/";
    filename << blockData->ChunkPosition.GetX();
    filename << '_';
    filename << blockData->ChunkPosition.GetY();
    filename << '_';
    filename << blockData->ChunkPosition.GetZ();
    filename << ".dat";

    std::ifstream file;
    file.open(filename.str());
    bool serialized = false;

    if (file.is_open())
    {        
        std::ostringstream search;
        search << "X";
        search << blockData->BlockPosition.m_x;
        search << "Y";
        search << blockData->BlockPosition.m_y;
        search << "Z";
        search << blockData->BlockPosition.m_z;
        search << ":";

        size_t pos;
        std::string line;
        while(std::getline(file,line))
        {
            pos=line.find(search.str());
            if(pos!=std::string::npos)
            {
                search << static_cast<unsigned short>(blockData->Type);
                search << '\n';
                line.replace(pos, search.str().length(), search.str());
                LOG("Replace File %s -> Line: %s : SearchLine %s", filename.str().c_str(), line.c_str(), search.str().c_str());
                serialized = true;
                break;                
            }
        }

        file.close();

        if(!serialized)
        {
            std::ofstream stream(filename.str(), std::ios_base::app | std::ios_base::out);
            stream << "X" << blockData->BlockPosition.m_x << "Y" << blockData->BlockPosition.m_y << "Z" << blockData->BlockPosition.m_z << ":" << static_cast<unsigned short>(blockData->Type) << '\n';
            stream.flush();
            stream.close();
            LOG("Add Line into file %s", filename.str().c_str());
        }
    }
    else
    {        
        std::ofstream stream(filename.str());

        stream << blockData->ChunkPosition.GetX() << ';' << blockData->ChunkPosition.GetY() << ';' << blockData->ChunkPosition.GetZ() << '\n';
        stream << "X" << blockData->BlockPosition.m_x << "Y" << blockData->BlockPosition.m_y << "Z" << blockData->BlockPosition.m_z << ":" << static_cast<unsigned short>(blockData->Type) << '\n';

        stream.flush();
        stream.close();
        LOG("Create File %s", filename.str().c_str());
    }

    thread->CleanUp<BlockChangeData>();
    thread->Release();  

    return nullptr;
}

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
#include<iostream>
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
    std::ifstream fstream;
    fstream.open(filepath);
    if (fstream.is_open())
    {
        std::string line;
        while (!fstream.eof())
        {
            std::getline(fstream, line);

        }
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
        while(file.good())
        {
            std::string line;
            std::getline(file,line); // get line from file
            LOG("Line: %s : SearchLine %s", line.c_str(), search.str().c_str());
            pos=line.find(search.str()); // search
            if(pos!=std::string::npos) // string::npos is returned if string is not found
            {
                search << static_cast<unsigned short>(blockData->Type);
                search << '\n';
                line.replace(pos, search.str().length(), search.str());
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
        }
    }
    else
    {        
        std::ofstream stream(filename.str());

        stream << blockData->ChunkPosition.GetX() << ';' << blockData->ChunkPosition.GetY() << ';' << blockData->ChunkPosition.GetZ() << '\n';
        stream << "X" << blockData->BlockPosition.m_x << "Y" << blockData->BlockPosition.m_y << "Z" << blockData->BlockPosition.m_z << ":" << static_cast<unsigned short>(blockData->Type) << '\n';

        stream.flush();
        stream.close();
    }

    thread->CleanUp<BlockChangeData>();
    thread->Release();  

    return nullptr;
}

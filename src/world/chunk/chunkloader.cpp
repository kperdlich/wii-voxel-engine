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

#include <string>
#include <algorithm>
#include "chunkloader.h"
#include "chunkserializer.h"
#include "../../utils/Filesystem.h"
#include "../../utils/Debug.h"

ChunkLoader::ChunkLoader()
{

}

void ChunkLoader::Init(const Vector3 &position, GameWorld *world)
{
    m_world = world;
    Vector3 currentChunkPos = GetChunkPositionByWorldPosition(position);
    LoadChunks(currentChunkPos);
    UpdateLoadedChunkNeighbors();
}

const std::vector<Chunk*> &ChunkLoader::GetLoadedChunks()
{
    return m_loadedChunks;
}

void ChunkLoader::UpdateChunksBy(const Vector3 &position)
{
    Vector3 currentChunkPos = GetChunkPositionByWorldPosition(position);

    if ( currentChunkPos != m_lastUpdateChunkPos )
    {        
        LoadChunks(currentChunkPos);
        UpdateLoadedChunkNeighbors();
    }

    CopyLoadedChunks();
}

Chunk* ChunkLoader::GetCashedChunkByWorldPosition(const Vector3& worldPosition)
{
    return GetChunkFromCash(GetChunkPositionByWorldPosition(worldPosition));
}

 std::vector<Chunk *>::iterator ChunkLoader::GetCashedChunkIterator(const Vector3 &chunkPosition)
{
    return std::find_if(m_loadedChunks.begin(), m_loadedChunks.end(), [&chunkPosition]( const Chunk* chunk){
        return chunk->GetCenterPosition() == chunkPosition;
    });
}

void ChunkLoader::UpdateLoadedChunkNeighbors()
{
    for (auto chunkIt : m_loadedChunks)
    {
        chunkIt->UpdateChunkNeighbors();
    }
}

Vector3 ChunkLoader::GetChunkPositionByWorldPosition(const Vector3 &worldPosition)
{
    int32_t x = ((int32_t) worldPosition.GetX() / (CHUNK_BLOCK_SIZE_X));
    int32_t z = ((int32_t) worldPosition.GetZ() / (CHUNK_BLOCK_SIZE_Z));

    double cX, cY, cZ;
    uint32_t chunkRadius = (CHUNK_BLOCK_SIZE_X / 2);
    cX = worldPosition.GetX() < 0 ? (x * CHUNK_BLOCK_SIZE_X) - chunkRadius : (x * CHUNK_BLOCK_SIZE_X) + chunkRadius;
    cY = CHUNK_BLOCK_SIZE_Y / 2;
    cZ = worldPosition.GetZ() < 0 ? (z * CHUNK_BLOCK_SIZE_X) - chunkRadius : (z * CHUNK_BLOCK_SIZE_X) + chunkRadius;

    return Vector3(cX, cY, cZ);
}

void ChunkLoader::RemoveChunkFromCash(const Vector3 &chunkPosition)
{
    auto it = GetCashedChunkIterator(chunkPosition);
    if (it != m_loadedChunks.end())
    {
        m_loadedChunks.erase(it);
    }
}

void ChunkLoader::DestroyChunkCash()
{
    for ( auto it = m_loadedChunks.begin(); it != m_loadedChunks.end(); it++)
    {
        delete (*it);
    }

    m_loadedChunks.clear();
}

void ChunkLoader::LoadChunks(const Vector3 &chunkPosition)
{
    LOG("Load Chunks");

    // 1. Get map of all necessary chunks
    // 2. Check if all loaded
    // 3. Get loading object and trigger loading

    double x = chunkPosition.GetX() - (2*CHUNK_BLOCK_SIZE_X);
    double z = chunkPosition.GetZ() + (2*CHUNK_BLOCK_SIZE_X);

    std::vector<Vector3> chunkMap;

    for ( uint32_t i = 0; i < CHUNK_MAP_CASH_X; i++)
    {
        for ( uint32_t j = 0; j < CHUNK_MAP_CASH_Y; j++)
        {
            chunkMap.emplace_back(Vector3(x+(i*CHUNK_BLOCK_SIZE_X), CHUNK_BLOCK_SIZE_Y / 2, z-(j*CHUNK_BLOCK_SIZE_Z)));
        }
    }

    std::vector<Chunk*> tmpChunkCash;
    for(auto& position : chunkMap)
    {
        auto cashedChunk = GetChunkFromCash(position);
        if ( cashedChunk )
        {
            RemoveChunkFromCash(position);
            tmpChunkCash.push_back(cashedChunk);
        }
        else
        {
            Chunk* chunk = new Chunk(*m_world);
            chunk->SetCenterPosition(position);
            chunk->Init();
            chunk->Build();
            chunk->SetDirty(true);
            std::string filename = ChunkSerializer::GetFilePath(position);
            if ( FileSystem::FileExist(filename))
            {
                ChunkLoadingData* chunkLoadingData = new ChunkLoadingData();
                chunkLoadingData->ChunkObj = chunk;
                chunkLoadingData->Filepath = filename;
                chunkLoadingData->LoadingDone = false;
                LWP_MutexInit(&chunkLoadingData->Mutex, false);
                m_chunkLoadingCash.push_back(chunkLoadingData);
                ChunkSerializer::Deserialize(chunkLoadingData);
            }
            else
            {
                tmpChunkCash.push_back(chunk);
            }
        }
    }

    chunkMap.clear();
    DestroyChunkCash();
    for (auto loadedChunk : tmpChunkCash)
    {
        m_loadedChunks.push_back(loadedChunk);
    }

    tmpChunkCash.clear();
    m_lastUpdateChunkPos = chunkPosition;
}

void ChunkLoader::CopyLoadedChunks()
{
    if(m_chunkLoadingCash.empty())
        return;

    for (auto iter = m_chunkLoadingCash.begin(); iter != m_chunkLoadingCash.end(); )
    {
        auto data = static_cast<ChunkLoadingData*>(*iter);

        uint32_t status = LWP_MutexLock(data->Mutex);
        if (status == 0)
        {
            if(data->LoadingDone)
            {
                data->ChunkObj->SetDirty(true);
                m_loadedChunks.push_back(data->ChunkObj);
                LWP_MutexUnlock(data->Mutex);
                LWP_MutexDestroy(data->Mutex);

                /*double x = data->ChunkObj->GetCenterPosition().GetX();
                double y = data->ChunkObj->GetCenterPosition().GetY();
                double z = data->ChunkObj->GetCenterPosition().GetZ();*/
                //LOG("Copyied %f %f %f", x, y, z);

                delete data;
                iter = m_chunkLoadingCash.erase(iter);
            }
            else
            {
                LWP_MutexUnlock(data->Mutex);
                //LOG("Unlocked but not done oO");
                ++iter;
            }
        }
        else
        {
            //LOG("Failed to lock");
            ++iter;
        }
    }

    if(m_chunkLoadingCash.empty())
        UpdateLoadedChunkNeighbors();
}

Chunk* ChunkLoader::GetChunkFromCash(const Vector3 &chunkPosition)
{
    auto it = GetCashedChunkIterator(chunkPosition);
    if (it != m_loadedChunks.end())
    {
        return (*it);
    }

    return nullptr;
}

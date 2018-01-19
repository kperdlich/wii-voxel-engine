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
#include "ChunkManager.h"
#include "ChunkData.h"
#include "chunkdata.h"
#include "../../utils/Job.h"
#include "Chunk.h"
#include "jobs/ChunkLoaderJob.h"
#include "jobs/SerializationJob.h"
#include "../GameWorld.h"
#include "../../utils/Filesystem.h"
#include "../../utils/Debug.h"

ChunkManager::~ChunkManager()
{
    m_loaderJob.Stop();
    m_serializationJob.Stop();
    DestroyChunkCash();
}

void ChunkManager::Init(const Vector3 &position, GameWorld *world)
{
    m_world = world;
    m_serializationJob.Start(QueueJob);
    m_loaderJob.Start(LoadChunkJob);

    Vector3 currentChunkPos = GetChunkPositionByWorldPosition(position);
    const auto& chunkMap = GetChunkMapAround(currentChunkPos);

    for (auto& pos : chunkMap)
    {
        Chunk* chunk = new Chunk(*m_world);
        chunk->Init();
        chunk->SetCenterPosition(pos);
        m_chunkCash.push_back(chunk);
    }

    LoadChunks(currentChunkPos);
}

const std::vector<Chunk*> ChunkManager::GetLoadedChunks() const
{
    std::vector<Chunk*> loadedChunks;
    for (Chunk* cc : m_chunkCash)
    {
        if(cc->IsLoaded() || cc->HasDisplayList())
        {
            loadedChunks.push_back(cc);
        }
    }

    return loadedChunks;
}

void ChunkManager::UpdateChunksBy(const Vector3 &position)
{
    for (auto it = m_chunkLoadingStage.begin(); it != m_chunkLoadingStage.end(); )
    {
        Chunk* c = (*it);
        if(c->IsLoaded() && c->NeighborsLoaded())
        {
            c->SetDirty(true);
            it = m_chunkLoadingStage.erase(it);
        }
        else
        {
            it++;
        }
    }

    Vector3 currentChunkPos = GetChunkPositionByWorldPosition(position);

    if ( currentChunkPos != m_lastUpdateChunkPos )
    {        
        LoadChunks(currentChunkPos);               
    }
}

Chunk* ChunkManager::GetCashedChunkByWorldPosition(const Vector3& worldPosition)
{
    return GetChunkFromCash(GetChunkPositionByWorldPosition(worldPosition));
}

void ChunkManager::Serialize(const BlockChangeData& data)
{
    m_serializationJob.Add(data);
}

std::vector<Chunk *>::iterator ChunkManager::GetCashedChunkIterator(const Vector3 &chunkPosition)
{
    return std::find_if(m_chunkCash.begin(), m_chunkCash.end(), [&chunkPosition]( const Chunk* chunk){
        return chunk->GetCenterPosition() == chunkPosition;
    });
}

void ChunkManager::SetChunkNeighbors()
{
    for (auto cc : m_chunkCash)
    {
        cc->SetChunkNeighbors();
    }
}

Vector3 ChunkManager::GetChunkPositionByWorldPosition(const Vector3 &worldPosition)
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

void ChunkManager::DestroyChunkCash()
{
    for ( auto it = m_chunkCash.begin(); it != m_chunkCash.end(); it++)
    {
        delete (*it);
    }

    m_chunkCash.clear();
}

void ChunkManager::LoadChunks(const Vector3 &chunkPosition)
{    
    auto chunkMap = GetChunkMapAround(chunkPosition);
    std::vector<Chunk*> chunkPreCashed;

    for(auto it = chunkMap.begin(); it != chunkMap.end();)
    {
        Vector3 pos = (*it);
        Chunk* chunk = GetChunkFromCash(pos);
        if (chunk && chunk->IsLoaded() && IsCloseToChunk(chunkPosition, pos))
        {
            chunkPreCashed.push_back(chunk);
            it = chunkMap.erase(it);
        }
        else
        {
            it++;
        }
    }

    for(uint32_t i = 0; i < m_chunkCash.size(); ++i)
    {        
        Chunk* chunk = m_chunkCash[i];

        auto it = std::find_if(chunkPreCashed.begin(), chunkPreCashed.end(), [&chunk]( const Chunk* cashedChunk){
                return cashedChunk->GetCenterPosition() == chunk->GetCenterPosition();
        });

        if (it != chunkPreCashed.end())
            continue;

        const Vector3& cPos = chunkMap.back();
        chunk->SetCenterPosition(cPos);
        chunk->SetLoaded(false);
        m_chunkLoadingStage.push_back(chunk);
        chunk->Build();
        chunkMap.pop_back();
        m_loaderJob.Add(ChunkLoadingData { chunk->GetFilePath(), chunk});
    }

    chunkPreCashed.clear();
    m_lastUpdateChunkPos = chunkPosition;
    SetChunkNeighbors();
}

std::vector<Vector3> ChunkManager::GetChunkMapAround(const Vector3 &chunkPosition) const
{
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

    return chunkMap;
}

bool ChunkManager::IsCloseToChunk(const Vector3& chunkPosition, const Vector3& position) const
{
    return ( chunkPosition.GetX() - (CHUNK_BLOCK_SIZE_X) >= position.GetX() ||
             chunkPosition.GetX() + (CHUNK_BLOCK_SIZE_X) <= position.GetX() ||
             chunkPosition.GetZ() - (CHUNK_BLOCK_SIZE_Z) >= position.GetZ() ||
             chunkPosition.GetZ() + (CHUNK_BLOCK_SIZE_Z) <= position.GetZ());
}

Chunk* ChunkManager::GetChunkFromCash(const Vector3 &chunkPosition)
{
    auto it = GetCashedChunkIterator(chunkPosition);
    if (it != m_chunkCash.end())
    {
        return (*it);
    }

    return nullptr;
}

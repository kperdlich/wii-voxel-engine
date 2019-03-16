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
#include <errno.h>
#include <algorithm>
#include "ChunkManager.h"
#include "chunkdata.h"
#include "../../utils/Job.h"
#include "Chunk.h"
#include "jobs/ChunkLoaderJob.h"
#include "jobs/SerializationJob.h"
#include "../GameWorld.h"
#include "../../utils/Filesystem.h"
#include "../../utils/Debug.h"
#include "../../utils/clock.h"

ChunkManager::~ChunkManager()
{
    m_loaderJob.Stop();
    m_serializationJob.Stop();
    DestroyChunkCash();

    int value = FileSystem::RemoveDirectory(WORLD_PATH);
    if (value == -1)
    {
        LOG("Couldn't not delete directory /world! Error: %s", strerror(errno));
    }
}

void ChunkManager::Init(const Vector3 &position, GameWorld *world)
{
    m_world = world;
    m_serializationJob.Start();
    m_loaderJob.Start();

    Vec2i currentChunkPos = GetChunkPositionByWorldPosition(position);
    const auto& chunkMap = GetChunkMapAround(currentChunkPos);

    for (auto& pos : chunkMap)
    {
        Chunk* chunk = new Chunk(*m_world);
        chunk->Init();
        chunk->SetPosition(pos);
        //chunk->Build();
        chunk->SetLoaded(false);
        chunk->SetToAir();
        m_chunkCash.push_back(chunk);
    }

    //LoadChunks(currentChunkPos);
}

const std::vector<Chunk*> ChunkManager::GetLoadedChunks() const
{
    std::vector<Chunk*> loadedChunks;
    for (Chunk* cc : m_chunkCash)
    {
        if (cc->IsLoaded() /*|| cc->HasDisplayList()*/)
        {
            loadedChunks.push_back(cc);
        }
    }

    return loadedChunks;
}

void ChunkManager::UpdateChunksBy(const Vector3 &position)
{    
    Clock clock;
    clock.Start();
    for (auto it = m_chunkLoadingStage.begin(); it != m_chunkLoadingStage.end(); )
    {
        Chunk* c = (*it);
        if (c->IsLoaded()/* && c->NeighborsLoaded()*/)
        {
            c->SetDirty(true);
            it = m_chunkLoadingStage.erase(it);
            //LOG("Loaded chunk: %d %d", c->GetPosition().X, c->GetPosition().Y);
        }
        else
        {
            it++;
        }
    }

    Vec2i currentChunkPos = GetChunkPositionByWorldPosition(position);

    if (currentChunkPos != m_lastUpdateChunkPos)
    {        
        LOG("   PlayerPos: %f %f %f, ChunkPos: %d %d", position.GetX(), position.GetY(), position.GetZ(),
            currentChunkPos.X, currentChunkPos.Y);
        LoadChunks(currentChunkPos);               
    }
    clock.Stop();
    if (clock.GetSecs() > 0.0f)
        LOG("   UpdateChunksBy took %f s", clock.GetSecs());
}

Chunk* ChunkManager::GetCashedChunkByWorldPosition(const Vector3& worldPosition)
{
    return GetChunkFromCash(GetChunkPositionByWorldPosition(worldPosition));
}

void ChunkManager::Serialize(const CompressedChunkData& data)
{
    m_serializationJob.Add(data);
}

std::vector<Chunk *>::iterator ChunkManager::GetCashedChunkIterator(const Vec2i &chunkPosition)
{
    return std::find_if(m_chunkCash.begin(), m_chunkCash.end(), [&chunkPosition]( const Chunk* chunk){
        return chunk->GetPosition() == chunkPosition;
    });
}

void ChunkManager::SetChunkNeighbors()
{
    for (auto cc : m_chunkCash)
    {
        cc->SetChunkNeighbors();
    }
}

Vec2i ChunkManager::GetChunkPositionByWorldPosition(const Vector3 &worldPosition)
{
    // todo current player position + current chunk position to debug server
    int32_t x = (int32_t) (std::floor(worldPosition.GetX() / CHUNK_BLOCK_SIZE_X));
    int32_t z = (int32_t) (std::floor(worldPosition.GetZ() / CHUNK_BLOCK_SIZE_Z));
    //LOG("worldPosition: %d %d %d, chunkPos: %d %d", (int32_t)worldPosition.GetX(), (int32_t)worldPosition.GetY(), (int32_t)worldPosition.GetZ(),
    //    x, z);
    return Vec2i(x, z);
}

void ChunkManager::DestroyChunkCash()
{
    for ( auto it = m_chunkCash.begin(); it != m_chunkCash.end(); it++)
    {
        delete (*it);
    }

    m_chunkCash.clear();
}

void ChunkManager::LoadChunks(const Vec2i &chunkPosition)
{
    Clock clock;
    clock.Start();
    auto chunkMap = GetChunkMapAround(chunkPosition);

    std::vector<Chunk*> chunkPreCashed;

    for(auto it = chunkMap.begin(); it != chunkMap.end();)
    {
        Vec2i pos = (*it);
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
                return cashedChunk->GetPosition() == chunk->GetPosition();
        });

        if (it != chunkPreCashed.end())
            continue;

        const Vec2i& cPos = chunkMap.back();
        chunk->SetPosition(cPos);
        chunk->SetLoaded(false);
        chunk->SetToAir();
        m_chunkLoadingStage.push_back(chunk);
        chunkMap.pop_back();
        m_loaderJob.Add(ChunkLoadingData {chunk});
        //LOG("Added Chunk to loading stage");
    }

    chunkPreCashed.clear();
    m_lastUpdateChunkPos = chunkPosition;
    SetChunkNeighbors();
    clock.Stop();
    LOG("       LoadChunks took %f s", clock.GetSecs());
}

std::vector<Vec2i> ChunkManager::GetChunkMapAround(const Vec2i &chunkPosition) const
{
    int32_t x = chunkPosition.X - (CHUNK_MAP_CASH_X/2);
    int32_t z = chunkPosition.Y + (CHUNK_MAP_CASH_Y/2);

    std::vector<Vec2i> chunkMap;

    for (uint32_t i = 0; i < CHUNK_MAP_CASH_X; i++)
    {
        for (uint32_t j = 0; j < CHUNK_MAP_CASH_Y; j++)
        {
            chunkMap.emplace_back(Vec2i(x+i, z-j));
        }
    }

    return chunkMap;
}

bool ChunkManager::IsCloseToChunk(const Vec2i& chunkPosition, const Vec2i& position) const
{
    return ( (chunkPosition.X == position.X) ||
             (chunkPosition.Y == position.Y) ||
             (chunkPosition.X - 1) == position.X ||
             (chunkPosition.X + 1) == position.X ||
             (chunkPosition.Y - 1) == position.Y ||
             (chunkPosition.Y + 1) == position.Y);
}

Chunk* ChunkManager::GetChunkFromCash(const Vec2i &position)
{
    auto it = GetCashedChunkIterator(position);
    if (it != m_chunkCash.end())
    {
        return (*it);
    }

    return nullptr;
}

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

#pragma once

#include <vector>
#include "chunkdata.h"
#include "jobs/SerializationJob.h"
#include "jobs/ChunkLoaderMultiplayer.h"
#include "../../utils/Vector3.h"

class ChunkManager
{
public:   
    ChunkManager();
    ChunkManager(const ChunkManager&) = delete;
    ChunkManager(ChunkManager&&) = delete;
    void operator=(const ChunkManager&) = delete;
    void operator=(ChunkManager&&) = delete;
    ~ChunkManager();
    void Init(const Vector3 &position, class GameWorld* world);
    const std::vector<Chunk *> GetLoadedChunks() const;
    void UpdateChunksBy(const Vector3 &position);
    class Chunk* GetChunkFromCash(const Vec2i &position);
    class Chunk* GetCashedChunkByWorldPosition(const Vector3 &worldPosition);


    void Serialize(const CompressedChunkData& data);

private:

    std::vector<Chunk*>::iterator GetCashedChunkIterator(const Vec2i &chunkPosition);

    Vec2i GetChunkPositionByWorldPosition(const Vector3 &worldPosition) const;
    void SetChunkNeighbors();   
    void DestroyChunkCash();
    void LoadChunks(const Vec2i& chunkPosition);
    std::vector<Vec2i> GetChunkMapAround(const Vec2i &chunkPosition) const;
    bool IsCloseToChunk(const Vec2i &chunkPosition, const Vec2i &position) const;

private:
    std::vector<class Chunk*> m_chunkCash;
    std::vector<class Chunk*> m_chunkLoadingStage;

    Vec2i m_lastUpdateChunkPos;
    class GameWorld* m_world;


    SerializationJob m_serializationJob;
    ChunkLoaderMultiplayer m_loaderJob;

    friend class GameWorld;
};

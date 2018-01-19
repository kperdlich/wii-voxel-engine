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

#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <vector>
#include "chunkdata.h"
#include "../../utils/Job.h"
#include "../../utils/Vector3.h"

class ChunkManager
{
public:   
    ~ChunkManager();
    void Init(const Vector3 &position, class GameWorld* world);
    const std::vector<Chunk *> GetLoadedChunks() const;
    void UpdateChunksBy(const Vector3& position);
    class Chunk* GetChunkFromCash( const Vector3& chunkPosition);    
    class Chunk* GetCashedChunkByWorldPosition(const Vector3& worldPosition);    

    void Serialize(const BlockChangeData& data);    

private:

    std::vector<Chunk*>::iterator GetCashedChunkIterator(const Vector3& chunkPosition);
    Vector3 GetChunkPositionByWorldPosition(const Vector3& worldPosition);
    void SetChunkNeighbors();   
    void DestroyChunkCash();
    void LoadChunks(const Vector3& chunkPosition);
    std::vector<Vector3> GetChunkMapAround(const Vector3& chunkPosition) const;
    bool IsCloseToChunk(const Vector3 & chunkPosition, const Vector3 &position) const;

private:
    std::vector<class Chunk*> m_chunkCash;
    std::vector<class Chunk*> m_chunkLoadingStage;

    Vector3 m_lastUpdateChunkPos;
    class GameWorld* m_world;

    Job<BlockChangeData> m_serializationJob;
    Job<ChunkLoadingData> m_loaderJob;
};

#endif // CHUNKMANAGER_H

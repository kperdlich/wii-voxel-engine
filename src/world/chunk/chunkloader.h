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

#ifndef CHUNKLOADER_H
#define CHUNKLOADER_H

#include <vector>
#include "chunkdata.h"
#include "chunkserializer.h"
#include "../../utils/Vector3.h"

class ChunkLoader
{
public:
    ChunkLoader();
    ~ChunkLoader();
    void Init(const Vector3 &position, class GameWorld* world);
    const std::vector<class Chunk*>& GetLoadedChunks();
    void UpdateChunksBy(const Vector3& position);
    class Chunk* GetChunkFromCash( const Vector3& chunkPosition);
    void CopyLoadedChunks();
    class Chunk* GetCashedChunkByWorldPosition(const Vector3& worldPosition);

    void Serialize(const BlockChangeData& data);

private:

    std::vector<Chunk *>::iterator GetCashedChunkIterator(const Vector3& chunkPosition);
    Vector3 GetChunkPositionByWorldPosition(const Vector3& worldPosition);
    void UpdateLoadedChunkNeighbors();
    void RemoveChunkFromCash(const Vector3& chunkPosition);
    void DestroyChunkCash();
    void LoadChunks(const Vector3& chunkPosition);

private:
    std::vector<class Chunk*> m_loadedChunks;
    std::vector<ChunkLoadingData*> m_chunkLoadingCash;
    Vector3 m_lastUpdateChunkPos;
    class GameWorld* m_world;
    ChunkSerializer m_serializer;

};

#endif // CHUNKLOADER_H

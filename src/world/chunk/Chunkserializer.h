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

#ifndef CHUNKSERIALIZER_H
#define CHUNKSERIALIZER_H

#include <vector>
#include <string>
#include <gccore.h>
#include "Chunk.h"
#include "../../utils/Vector3.h"
#include "../blocks/BlockManager.h"


struct ChunkSerializeData
{
    BlockType*** BlockData = nullptr;
    Vector3 ChunkCenter;
    bool Available = true;
    lwp_t Thread;

    ChunkSerializeData(BlockType*** blockData = nullptr) : BlockData(blockData){ }
};

class ChunkSerializer
{
public:
    ChunkSerializer();
    ~ChunkSerializer();

    void Init();
    static void Serialize(const class Chunk& chunk, const struct BlockChangeData* data);
    static void Deserialize(const std::string& filepath, Chunk* chunk);

    std::vector<ChunkSerializeData>& GetChunkCash()
    {
        return m_serializeChunkCash;
    }

private:
    std::vector<ChunkSerializeData> m_serializeChunkCash;
    bool m_bInitalized = false;
};

#endif // CHUNKSERIALIZER_H

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

#include "../blocks/BlockManager.h"
#include "../../utils/vecint.h"

#define CHUNK_MAP_CASH_X 5
#define CHUNK_MAP_CASH_Y 5

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16

#define CHUNK_BLOCK_SIZE_X (BLOCK_SIZE * CHUNK_SIZE_X)
#define CHUNK_BLOCK_SIZE_Y (BLOCK_SIZE * CHUNK_SIZE_Y)
#define CHUNK_BLOCK_SIZE_Z (BLOCK_SIZE * CHUNK_SIZE_Z)

#define CHUNK_GLOBAL_X(value) value * CHUNK_BLOCK_SIZE_X
#define CHUNK_GLOBAL_Z(value) value * CHUNK_BLOCK_SIZE_Z

struct CompressedChunkData
{
    int32_t m_X;
    int32_t m_Z;
    bool m_bGroundUpCon;
    uint16_t m_PrimaryBitMap;
    uint16_t m_AddBitMap;
    int32_t m_CompressedSize;
    unsigned char* m_CompressedData;
};

struct BlockChangeData
{
    std::string Filepath;
    BlockType   Type;
    Vec3i       BlockPosition;
    Vec2i       ChunkPosition;
};

struct ChunkLoadingData
{
    class Chunk*    ChunkObj;
};

/***
 *
 * Copyright (C) 2016 DaeFennek
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

#include <map>
#include <vector>
#include "Block.h"
#include "../../renderer/BlockRenderer.h"
#include "../../utils/Vector3.h"

constexpr float BLOCK_SIZE_HALF = .5;
constexpr float BLOCK_SIZE = BLOCK_SIZE_HALF * 2;

enum class BlockType : unsigned char
{
    AIR     = 0,
    STONE   = 4,
    GRASS   = 2,
    DIRT    = 3,
    WOOD    = 17,
    LEAF    = 18
};

class BlockManager {
public:
    BlockManager();
    BlockManager(const BlockManager&) = delete;
    BlockManager(BlockManager&&) = delete;
    void operator=(const BlockManager&) = delete;
    void operator=(BlockManager&&) = delete;
	virtual ~BlockManager();

	void LoadBlocks();
	void UnloadBlocks();

	Block* GetBlockByType(const BlockType type);

private:

    const Texture* AddToTextureList(const Texture* texture);

	std::map<BlockType, Block*> m_blocks;
	std::map<BlockType, std::vector<Vector3*> > m_mBlockRenderList;
    std::vector<const Texture*> m_textures;
	BlockRenderer* m_blockRenderer;

};

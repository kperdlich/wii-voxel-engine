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

#include "BlockManager.h"
#include "world/Frustrum.h"
#include "world/GameWorld.h"
#include "utils/Vector3.h"
#include "utils/Debug.h"

#include "Dirt_tpl.h"
#include "Grass_tpl.h"
#include "Grass_Side_tpl.h"
#include "Stone_tpl.h"
#include "Wood_tpl.h"
#include "Leaf_tpl.h"
#include "Tree_tpl.h"

void BlockManager::LoadBlocks()
{
	const Texture* pDirtTexture = AddToTextureList(Texture::Create(Dirt_tpl, Dirt_tpl_size));
	const Texture* pGrassTexture = AddToTextureList(Texture::Create(Grass_tpl, Grass_tpl_size));
	const Texture* pGrassSideTexture = AddToTextureList(Texture::Create(Grass_Side_tpl, Grass_Side_tpl_size));
	const Texture* pStoneTexture = AddToTextureList(Texture::Create(Stone_tpl, Stone_tpl_size));
	const Texture* pWoodTexture = AddToTextureList(Texture::Create(Wood_tpl, Wood_tpl_size));
	const Texture* pLeafTexture = AddToTextureList(Texture::Create(Leaf_tpl, Leaf_tpl_size));
	const Texture* pTreeTexture = AddToTextureList(Texture::Create(Tree_tpl, Tree_tpl_size));

	std::map<const Texture*, std::vector<EBlockFaces>> dirtTextureMap =
	{
		{
		  pDirtTexture,
		  {
			  EBlockFaces::Left,
			  EBlockFaces::Right,
			  EBlockFaces::Front,
			  EBlockFaces::Back,
			  EBlockFaces::Top,
			  EBlockFaces::Bottom,
		  }
		}
	};

	std::map<const Texture*, std::vector<EBlockFaces>> stoneTextureMap =
	{
		{
		  pStoneTexture,
		  {
			  EBlockFaces::Left,
			  EBlockFaces::Right,
			  EBlockFaces::Front,
			  EBlockFaces::Back,
			  EBlockFaces::Top,
			  EBlockFaces::Bottom,
		  }
		}
	};

	std::map<const Texture*, std::vector<EBlockFaces>> leafTextureMap =
	{
		{
		  pLeafTexture,
		  {
			  EBlockFaces::Left,
			  EBlockFaces::Right,
			  EBlockFaces::Front,
			  EBlockFaces::Back,
			  EBlockFaces::Top,
			  EBlockFaces::Bottom,
		  }
		}
	};

	std::map<const Texture*, std::vector<EBlockFaces>> grassTextureMap =
	{
		{
			pGrassTexture,
			{
				  EBlockFaces::Top
			}
		},
		{
			pDirtTexture,
			{
				  EBlockFaces::Bottom
			}
		},
		{
			pGrassSideTexture,
			{
				EBlockFaces::Left,
				EBlockFaces::Right,
				EBlockFaces::Front,
				EBlockFaces::Back
			}
		}
	};

	std::map<const Texture*, std::vector<EBlockFaces>> woodTextureMap =
	{
		{
			pTreeTexture,
			{
				  EBlockFaces::Top,
				  EBlockFaces::Bottom
			}
		},
		{
			pWoodTexture,
			{
				EBlockFaces::Left,
				EBlockFaces::Right,
				EBlockFaces::Front,
				EBlockFaces::Back
			}
		}
	};

	m_blocks.insert(std::pair< BlockType, Block* >(BlockType::AIR, new Block(BLOCK_SIZE_HALF, {}))); // no texture for air!
	m_blocks.insert(std::pair< BlockType, Block* >(BlockType::DIRT, new Block(BLOCK_SIZE_HALF, dirtTextureMap)));
	m_blocks.insert(std::pair< BlockType, Block* >(BlockType::GRASS, new Block(BLOCK_SIZE_HALF, grassTextureMap)));
	m_blocks.insert(std::pair< BlockType, Block* >(BlockType::STONE, new Block(BLOCK_SIZE_HALF, stoneTextureMap)));
	m_blocks.insert(std::pair< BlockType, Block* >(BlockType::WOOD, new Block(BLOCK_SIZE_HALF, woodTextureMap)));
	m_blocks.insert(std::pair< BlockType, Block* >(BlockType::LEAF, new Block(BLOCK_SIZE_HALF, leafTextureMap)));
}

void BlockManager::UnloadBlocks()
{
	for (auto blockIterator = m_blocks.begin(); blockIterator != m_blocks.end(); blockIterator++)
	{
		delete blockIterator->second;
	}

	m_blocks.clear();

	for (auto texture : m_textures)
	{
		delete texture;
	}
}


BlockManager::BlockManager() {}

BlockManager::~BlockManager() {}


Block* BlockManager::GetBlockByType(const BlockType type)
{
	auto blockIterator = m_blocks.find(type);
	if (blockIterator != m_blocks.end())
	{
		return blockIterator->second;
	}

	return nullptr;
}

const Texture* BlockManager::AddToTextureList(const Texture* texture)
{
	m_textures.push_back(texture);
	return texture;
}

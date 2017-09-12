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
#include "../Frustrum.h"
#include "../GameWorld.h"
#include "../../utils/Vector3.h"
#include "../../utils/Debug.h"

#include "Dirt_tpl.h"
#include "Grass_tpl.h"
#include "Grass_Side_tpl.h"
#include "Stone_tpl.h"
#include "Wood_tpl.h"
#include "Leaf_tpl.h"
#include "Tree_tpl.h"

void BlockManager::LoadBlocks()
{
    Texture* pDirtTexture = m_pTextureHandler->CreateTexture(Dirt_tpl, Dirt_tpl_size, BLOCK_TEXTURE_DIRT );
    Texture* pGrassTexture = m_pTextureHandler->CreateTexture(Grass_tpl, Grass_tpl_size, BLOCK_TEXTURE_GRASS );
    Texture* pGrassSideTexture = m_pTextureHandler->CreateTexture(Grass_Side_tpl, Grass_Side_tpl_size, BLOCK_TEXTURE_GRASS_SIDE );
    Texture* pStoneTexture = m_pTextureHandler->CreateTexture(Stone_tpl, Stone_tpl_size, BLOCK_TEXTURE_STONE );
    Texture* pWoodTexture = m_pTextureHandler->CreateTexture(Wood_tpl, Wood_tpl_size, BLOCK_TEXTURE_WOOD );
    Texture* pLeafTexture = m_pTextureHandler->CreateTexture(Leaf_tpl, Leaf_tpl_size, BLOCK_TEXTURE_LEAF );
    Texture* pTreeTexture = m_pTextureHandler->CreateTexture(Tree_tpl, Tree_tpl_size, BLOCK_TEXTURE_TREE );

    // todo dirty workaround - have to fix texture handler
    pDirtTexture->SetVisible(false);
    pGrassTexture->SetVisible(false);
    pGrassSideTexture->SetVisible(false);
    pStoneTexture->SetVisible(false);
    pWoodTexture->SetVisible(false);
    pLeafTexture->SetVisible(false);
    pTreeTexture->SetVisible(false);

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

    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::AIR, new Block( BLOCK_SIZE_HALF, {}))); // no texture for air!
    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::DIRT, new Block( BLOCK_SIZE_HALF, dirtTextureMap )));
    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::GRASS, new Block( BLOCK_SIZE_HALF, grassTextureMap)));
    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::STONE, new Block( BLOCK_SIZE_HALF, stoneTextureMap)));
    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::WOOD, new Block( BLOCK_SIZE_HALF, woodTextureMap)));
    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::LEAF, new Block( BLOCK_SIZE_HALF, leafTextureMap)));
}

void BlockManager::UnloadBlocks()
{
	for ( auto blockIterator = m_blocks.begin(); blockIterator != m_blocks.end(); blockIterator++ )
	{
		delete blockIterator->second;
	}

	m_blocks.clear();
}


BlockManager::BlockManager( TextureHandler& ptextureHandler) {
	m_pTextureHandler = &ptextureHandler;
}

BlockManager::~BlockManager() {}


Block* BlockManager::GetBlockByType(const BlockType type)
{
	auto blockIterator = m_blocks.find(type);
	if ( blockIterator != m_blocks.end() )
	{
		return blockIterator->second;
	}

    return nullptr;
}

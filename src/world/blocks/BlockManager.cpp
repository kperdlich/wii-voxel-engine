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

#include "Dirt_png.h"
#include "Grass_png.h"
#include "Grass_Side_png.h"

void BlockManager::LoadBlocks()
{
    Texture* pDirtTexture = m_pTextureHandler->CreateTexture( Dirt_png, BLOCK_TEXTURE_DIRT );
    Texture* pGrassTexture = m_pTextureHandler->CreateTexture( Grass_png, BLOCK_TEXTURE_GRASS );
    Texture* pGrassSideTexture = m_pTextureHandler->CreateTexture( Grass_Side_png, BLOCK_TEXTURE_GRASS_SIDE );

    // todo dirty workaround - have to fix texture handler
    pDirtTexture->SetVisible(false);
    pGrassTexture->SetVisible(false);
    pGrassSideTexture->SetVisible(false);

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

    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::AIR, new Block( BLOCK_SIZE_HALF, {}))); // no texture for air!
    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::DIRT, new Block( BLOCK_SIZE_HALF, dirtTextureMap )));
    m_blocks.insert(std::pair< BlockType, Block* >( BlockType::GRASS, new Block( BLOCK_SIZE_HALF, grassTextureMap)));
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

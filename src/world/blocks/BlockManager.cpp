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
#include "../CFrustrum.h"
#include "../GameWorld.h"
#include "../../utils/Vector3.h"
#include "../../utils/Debug.h"
#include "GroundText_png.h"
#include "Grass_png.h"

void CBlockManager::LoadBlocks()
{
	// todo dirty workaround - have to fix texture handler
	m_pTextureHandler->CreateTexture( GroundText_png, BLOCK_TEXTURE_DIRT )->SetVisible(false);
	m_pTextureHandler->CreateTexture( Grass_png, BLOCK_TEXTURE_GRASS )->SetVisible(false);

	m_blocks.insert(std::pair< BlockType, CBlock* >( BlockType::AIR, new CBlock( BLOCK_SIZE, NULL))); // no texture for air!
	m_blocks.insert(std::pair< BlockType, CBlock* >( BlockType::DIRT, new CBlock( BLOCK_SIZE, dynamic_cast<const Texture*>(m_pTextureHandler->GetTexture(BLOCK_TEXTURE_DIRT)))));
	m_blocks.insert(std::pair< BlockType, CBlock* >( BlockType::GRASS, new CBlock( BLOCK_SIZE, dynamic_cast<const Texture*>(m_pTextureHandler->GetTexture(BLOCK_TEXTURE_GRASS)))));
}

void CBlockManager::UnloadBlocks()
{
	for ( auto blockIterator = m_blocks.begin(); blockIterator != m_blocks.end(); blockIterator++ )
	{
		delete blockIterator->second;
	}

	m_blocks.clear();
}


CBlockManager::CBlockManager( TextureHandler& ptextureHandler) {
	m_pTextureHandler = &ptextureHandler;
}

CBlockManager::~CBlockManager() {}


CBlock* CBlockManager::GetBlockByType(const BlockType type)
{
	auto blockIterator = m_blocks.find(type);
	if ( blockIterator != m_blocks.end() )
	{
		return blockIterator->second;
	}

	return NULL;
}

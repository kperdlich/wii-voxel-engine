/*
 * BlockManager.cpp
 *
 *  Created on: 23.01.2016
 *      Author: Kevin
 */

#include "BlockManager.h"
#include "../CFrustrum.h"
#include "../GameWorld.h"
#include "../../../utils/Vector3f.h"
#include "../../../utils/Debug.h"
#include "GroundText_png.h"
#include "Grass_png.h"

void CBlockManager::LoadBlocks()
{
	// todo kperdlich dirty workaround - have to fix texture handler
	m_pTextureHandler->createTexture( GroundText_png, BLOCK_TEXTURE_DIRT )->setVisible(false);
	m_pTextureHandler->createTexture( Grass_png, BLOCK_TEXTURE_GRASS )->setVisible(false);

	m_blocks.insert(std::pair< BlockType, CBlock* >( BlockType::AIR, new CBlock( BLOCK_SIZE, NULL))); // no texture for air!
	m_blocks.insert(std::pair< BlockType, CBlock* >( BlockType::DIRT, new CBlock( BLOCK_SIZE, dynamic_cast<Texture*>(m_pTextureHandler->GetTexture(BLOCK_TEXTURE_DIRT)))));
	m_blocks.insert(std::pair< BlockType, CBlock* >( BlockType::GRASS, new CBlock( BLOCK_SIZE, dynamic_cast<Texture*>(m_pTextureHandler->GetTexture(BLOCK_TEXTURE_GRASS)))));
}

void CBlockManager::UnloadBlocks()
{
	for ( auto blockIterator = m_blocks.begin(); blockIterator != m_blocks.end(); blockIterator++ )
	{
		delete blockIterator->second;
	}

	m_blocks.clear();
}


CBlockManager::CBlockManager( TextureHandler* ptextureHandler) : m_pTextureHandler(ptextureHandler) {}

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

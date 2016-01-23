/*
 * BlockManager.cpp
 *
 *  Created on: 23.01.2016
 *      Author: Kevin
 */

#include "BlockManager.h"
#include "../../../utils/Vector3f.h"
#include "GroundText_png.h"
#include "Grass_png.h"

void CBlockManager::LoadBlocks()
{
	m_pTextureHandler->createTexture( GroundText_png, BLOCK_TEXTURE_DIRT )->setVisible(false);
	m_pTextureHandler->createTexture( Grass_png, BLOCK_TEXTURE_GRASS )->setVisible(false);

	m_blocks.insert(std::pair< int, CBlock* >( BLOCK_TYPE_DIRT, new CBlock( BLOCK_SIZE, dynamic_cast<Texture*>(m_pTextureHandler->GetTexture(BLOCK_TEXTURE_DIRT)))));
	m_blocks.insert(std::pair< int, CBlock* >( BLOCK_TYPE_GRASS, new CBlock( BLOCK_SIZE, dynamic_cast<Texture*>(m_pTextureHandler->GetTexture(BLOCK_TEXTURE_GRASS)))));
}

void CBlockManager::UnloadBlocks()
{
	for ( std::map<int, CBlock*>::iterator blockIterator = m_blocks.begin(); blockIterator != m_blocks.end(); blockIterator++ )
	{
		delete blockIterator->second;
	}

	m_blocks.clear();
}


CBlockManager::CBlockManager( TextureHandler* ptextureHandler) : m_pTextureHandler(ptextureHandler) {
	m_blockRenderer = new BlockRenderer();

}

CBlockManager::~CBlockManager() {
	delete m_blockRenderer;
}


CBlock* CBlockManager::GetBlockByType(unsigned int type)
{
	std::map<int, CBlock*>::iterator blockIterator = m_blocks.find(type);
	if ( blockIterator != m_blocks.end() )
	{
		return blockIterator->second;
	}

	return NULL;
}

void CBlockManager::Render(Vector3f position, unsigned int blockType)
{
	CBlock* pBlockToRender = GetBlockByType(blockType);
	m_blockRenderer->render( position, pBlockToRender->getSize(), pBlockToRender->GetTexture() );
}

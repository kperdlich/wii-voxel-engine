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
	// todo kperdlich dirty workaround - have to fix texture handler
	m_pTextureHandler->createTexture( GroundText_png, BLOCK_TEXTURE_DIRT )->setVisible(false);
	m_pTextureHandler->createTexture( Grass_png, BLOCK_TEXTURE_GRASS )->setVisible(false);

	m_blocks.insert(std::pair< int, CBlock* >( BLOCK_TYPE_DIRT, new CBlock( BLOCK_SIZE, dynamic_cast<Texture*>(m_pTextureHandler->GetTexture(BLOCK_TEXTURE_DIRT)))));
	m_blocks.insert(std::pair< int, CBlock* >( BLOCK_TYPE_GRASS, new CBlock( BLOCK_SIZE, dynamic_cast<Texture*>(m_pTextureHandler->GetTexture(BLOCK_TEXTURE_GRASS)))));
}

void CBlockManager::UnloadBlocks()
{
	for ( std::map<unsigned int, CBlock*>::iterator blockIterator = m_blocks.begin(); blockIterator != m_blocks.end(); blockIterator++ )
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

	ClearBlockRenderList();
}


CBlock* CBlockManager::GetBlockByType(unsigned int type)
{
	std::map<unsigned int, CBlock*>::iterator blockIterator = m_blocks.find(type);
	if ( blockIterator != m_blocks.end() )
	{
		return blockIterator->second;
	}

	return NULL;
}


bool CBlockManager::AddBlockToRenderList(unsigned int iBlockType, Vector3f* position)
{
	bool bSuccessful = false;
	std::map<unsigned int, std::vector<Vector3f*> >::iterator blockRenderListIt = m_mBlockRenderList.find(iBlockType);
	if (blockRenderListIt != m_mBlockRenderList.end())
	{
		blockRenderListIt->second.push_back(position);
		bSuccessful = true;
	}
	else
	{
		std::vector<Vector3f*> blockList;
		blockList.push_back(position);
		m_mBlockRenderList.insert(std::pair<unsigned int, std::vector<Vector3f*> >(iBlockType, blockList ));
		bSuccessful = true;
	}
	return bSuccessful;
}

void CBlockManager::RenderBlockList()
{
	for(std::map<unsigned int, std::vector<Vector3f*> >::iterator it = m_mBlockRenderList.begin(); it != m_mBlockRenderList.end(); ++it)
	{
		CBlock* pBlockToRender = GetBlockByType(it->first);
		m_blockRenderer->Prepare( &it->second, pBlockToRender->getSize(), pBlockToRender->GetTexture() );
		m_blockRenderer->render();
		m_blockRenderer->Finish();
	}
}

void CBlockManager::ClearBlockRenderList()
{
	for(std::map<unsigned int, std::vector<Vector3f*> >::iterator renderListIt = m_mBlockRenderList.begin(); renderListIt != m_mBlockRenderList.end(); ++renderListIt)
	{
		for(std::vector<Vector3f*>::iterator blockIt = renderListIt->second.begin(); blockIt != renderListIt->second.end(); ++blockIt)
		{
			delete (*blockIt);
		}
	}

	m_mBlockRenderList.clear();
}

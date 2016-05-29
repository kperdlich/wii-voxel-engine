/*
 * GameWorld.cpp
 *
 *  Created on: 23.01.2016
 *      Author: Kevin
 */

#include "GameWorld.h"

CGameWorld::CGameWorld( Basic3DScene* pScene ) : m_pScene(pScene)
{
	m_blockManager = new CBlockManager( pScene->getTextureHandler() );
	m_blockManager->LoadBlocks();

}

CGameWorld::~CGameWorld() {
	m_blockManager->UnloadBlocks();
	delete m_blockManager;
}

void CGameWorld::GenerateWorld()
{
	for ( unsigned int x = 0; x < WORLD_X; x++)
	{
		for ( unsigned int y = 0; y < WORLD_Y; y++ )
		{
			for ( unsigned int z = 0; z < WORLD_Z; z++)
			{
				unsigned int blockType = x % 2 == 0 ? BLOCK_TYPE_DIRT : BLOCK_TYPE_GRASS;
				m_worldMap[x][y][z] = blockType;
				m_blockManager->AddBlockToRenderList(blockType, *(new Vector3f( (x * BLOCK_SIZE) * 2, (y * BLOCK_SIZE) * 2, (z * BLOCK_SIZE) * 2)));
			}
		}
	}
}


void CGameWorld::Draw()
{
	m_blockManager->RenderBlockList();
}


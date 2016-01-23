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
				m_worldMap[x][y][z] = x % 2 == 0 ? BLOCK_TYPE_DIRT : BLOCK_TYPE_GRASS;
			}
		}
	}
}


void CGameWorld::Draw()
{
	for ( unsigned int x = 0; x < WORLD_X; x++)
	{
		for ( unsigned int y = 0; y < WORLD_Y; y++ )
		{
			for ( unsigned int z = 0; z < WORLD_Z; z++)
			{
				m_blockManager->Render(Vector3f( (x * BLOCK_SIZE) * 2, (y * BLOCK_SIZE) * 2, (z * BLOCK_SIZE) * 2), m_worldMap[x][y][z]);
			}
		}
	}
}


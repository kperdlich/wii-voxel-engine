/*
 * GameWorld.cpp
 *
 *  Created on: 23.01.2016
 *      Author: Kevin
 */

#include <stdint.h>
#include <string>
#include <inttypes.h>
#include "GameWorld.h"
#include "CFrustrum.h"
#include "../../utils/Debug.h"


CGameWorld::CGameWorld( Basic3DScene* pScene ) : m_pScene(pScene)
{
	m_blockManager = new CBlockManager( pScene->getTextureHandler() );
	m_blockManager->LoadBlocks();

#ifdef DEBUG
	m_pChunkLogBuffer = new char[50];
	m_pDisplayListSizeLogBuffer = new char[50];
	m_pBlocksLogBuffer = new char[50];
	m_pFaceLogBuffer = new char[50];
#endif
}

CGameWorld::~CGameWorld()
{	
	delete m_blockManager;

	delete[] m_pChunkLogBuffer;
	delete[] m_pDisplayListSizeLogBuffer;
	delete[] m_pBlocksLogBuffer;
	delete[] m_pFaceLogBuffer;

	for (auto chunkEntry : m_ChunkList)
	{
		delete chunkEntry.first;
		delete chunkEntry.second;
	}

	m_ChunkList.clear();
	
	m_blockManager->UnloadBlocks();
}

void CGameWorld::GenerateWorld()
{
	for ( unsigned int x = 0; x < CHUNK_AMOUNT_X; x++)
	{
		for ( unsigned int z = 0; z < CHUNK_AMOUNT_Z; z++)
		{
			auto pChunk = new CChunk(*this);
			auto pPosition = new Vector3f((float) (CHUNK_SIZE_X * x) + (CHUNK_SIZE_X / 2),  (float)CHUNK_SIZE_Y / 2, (float) (CHUNK_SIZE_Z * z) + (CHUNK_SIZE_Z / 2));
			m_ChunkList.insert(std::pair<Vector3f*, CChunk*>( pPosition, pChunk ));
			pChunk->Init( *pPosition );
		}
	}

	for (auto chunkEntry : m_ChunkList)
	{
		chunkEntry.second->UpdateChunkNeighbors();
	}
}


void CGameWorld::Draw()
{

#ifdef DEBUG
	uint32_t displayListSize = 0;
	uint32_t blocks = 0;
	uint32_t faces = 0;
	uint32_t activeFaces = 0;
	uint32_t activeBlocks = 0;
	uint32_t chunksInFrustrum = 0;
#endif

	auto playerPosition = m_pScene->GetEntityHandler().GetPlayer()->GetPosition();

	CFrustrum::Instance().CalculateFrustum();

	for( auto chunkEntry : m_ChunkList)
	{
		auto chunk = chunkEntry.second;
#ifdef DEBUG
		displayListSize += chunk->GetDisplayListSize();
		blocks += chunk->GetAmountOfBlocks();
		faces += chunk->GetAmountOfFaces();
#endif

		auto chunkPosition = chunk->GetCenterPosition();		

		if ( ChunkInFov(chunkPosition, playerPosition, CHUNK_PLAYER_FOV) )
		{
			if ( chunk->IsDirty() )
			{
				chunk->RebuildDisplayList();
			}
			chunk->Render();

			#ifdef DEBUG
				chunksInFrustrum++;
				activeBlocks += chunk->GetAmountOfBlocks();
				activeFaces += chunk->GetAmountOfFaces();
			#endif
		}
		else
		{
			chunk->DeleteDisplayList();
		}
		
	}

	// todo boost the performance of debug logs
#ifdef DEBUG
	sprintf(m_pChunkLogBuffer, "Rendered Chunks: %d/%d", chunksInFrustrum, m_ChunkList.size());
	Debug::getInstance().log( m_pChunkLogBuffer );

	sprintf(m_pDisplayListSizeLogBuffer, "DisplayList size (MB): %d", displayListSize / 1024 / 1024);
	Debug::getInstance().log( m_pDisplayListSizeLogBuffer );

	sprintf(m_pBlocksLogBuffer, "Blocks: %" PRId32 "/%" PRId32, activeBlocks, blocks);
	Debug::getInstance().log( m_pBlocksLogBuffer );

	sprintf(m_pFaceLogBuffer, "Faces: %" PRId32 "/%" PRId32, activeFaces, faces);
	Debug::getInstance().log( m_pFaceLogBuffer );
#endif

}

bool CGameWorld::ChunkInFov( Vector3f& chunkPosition, Vector3f& playerPosition, unsigned int fov)
{
	return (std::abs(chunkPosition.GetX() - playerPosition.GetX()) < CHUNK_SIZE_X * fov) &&
			(std::abs(chunkPosition.GetZ() - playerPosition.GetZ()) < CHUNK_SIZE_Z * fov);
}

CBlockManager& CGameWorld::GetBlockManager()
{
	return *m_blockManager;
}

CChunk* CGameWorld::GetChunkAt(Vector3f& centerPosition)
{
	auto chunkIt = m_ChunkList.find(&centerPosition);
	if (chunkIt != m_ChunkList.end())
	{
		return chunkIt->second;
	}
	return NULL;
}

CChunk* CGameWorld::GetChunkByWorldPosition(Vector3f& worldPosition)
{
	unsigned int x = worldPosition.GetX() / CHUNK_SIZE_X;
	unsigned int z = worldPosition.GetZ() / CHUNK_SIZE_Z;

	Vector3f chunkCenterPosition((x * CHUNK_SIZE_X) + (CHUNK_SIZE_X / 2), CHUNK_SIZE_Y / 2, (z * CHUNK_SIZE_Z) + (CHUNK_SIZE_Z / 2));

	return GetChunkAt(chunkCenterPosition);
}

void CGameWorld::RemoveBlockByWorldPosition(Vector3f blockPosition)
{
	auto pChunk = GetChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		pChunk->RemoveBlockByWorldPosition( blockPosition );
	}
}



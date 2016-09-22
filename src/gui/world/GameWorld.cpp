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
#ifdef DEBUG
	delete[] m_pChunkLogBuffer;
	delete[] m_pDisplayListSizeLogBuffer;
	delete[] m_pBlocksLogBuffer;
	delete[] m_pFaceLogBuffer;
#endif

	for (auto chunkEntry : m_ChunkList)
	{
		delete chunkEntry.first;
		delete chunkEntry.second;
	}
	m_ChunkList.clear();

	m_blockManager->UnloadBlocks();
	delete m_blockManager;
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
	uint64_t blocks = 0;
	uint64_t faces = 0;
	uint64_t activeFaces = 0;
	uint64_t activeBlocks = 0;
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

		// todo check chunk in view frustrum
		/*if ( CFrustrum::Instance().CubeInFrustum(
				chunkPosition.GetX() - (CHUNK_SIZE_X / 2),
				chunkPosition.GetY() - (CHUNK_SIZE_Y / 2),
				chunkPosition.GetZ() - (CHUNK_SIZE_Z / 2),
				chunkPosition.GetX() + (CHUNK_SIZE_X / 2),
				chunkPosition.GetY() + (CHUNK_SIZE_Y / 2),
				chunkPosition.GetZ() + (CHUNK_SIZE_Z / 2)))
		{*/

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
		//}
	}

	DrawFocusOnSelectedCube();

	// todo boost the performance of debug logs
#ifdef DEBUG
	sprintf(m_pChunkLogBuffer, "Rendered Chunks: %d/%d", chunksInFrustrum, m_ChunkList.size());
	Debug::getInstance().log( m_pChunkLogBuffer );

	//sprintf(m_pDisplayListSizeLogBuffer, "DisplayList size (MB): %d", displayListSize / 1024 / 1024);
	//Debug::getInstance().log( m_pDisplayListSizeLogBuffer );

	//ssprintf(m_pBlocksLogBuffer, "Blocks: %" PRId64 "/%" PRId64, activeBlocks, blocks);
	//sDebug::getInstance().log( m_pBlocksLogBuffer );

	//ssprintf(m_pFaceLogBuffer, "Faces: %" PRId64 "/%" PRId64, activeFaces, faces);
	//sDebug::getInstance().log( m_pFaceLogBuffer );
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

// todo replace param vector with floats
CChunk* CGameWorld::GetChunkByWorldPosition(Vector3f& worldPosition)
{
	unsigned int x = worldPosition.GetX() / CHUNK_SIZE_X;
	unsigned int z = worldPosition.GetZ() / CHUNK_SIZE_Z;

	Vector3f chunkCenterPosition((x * CHUNK_SIZE_X) + (CHUNK_SIZE_X / 2), CHUNK_SIZE_Y / 2, (z * CHUNK_SIZE_Z) + (CHUNK_SIZE_Z / 2));

	return GetChunkAt(chunkCenterPosition);
}

void CGameWorld::RemoveBlockByWorldPosition(Vector3f& blockPosition)
{
	auto pChunk = GetChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		pChunk->RemoveBlockByWorldPosition( blockPosition );
	}
}

void CGameWorld::UpdateFocusedBlockByWorldPosition( Vector3f& blockPosition )
{
	auto pChunk = GetChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		m_SelectedBlockPosition = pChunk->GetBlockPositionByWorldPosition( blockPosition );
		m_bHasSelectedBlock = true;
	}
	else
	{
		m_bHasSelectedBlock = false;
	}
}

Vector3f CGameWorld::GetBlockPositionByWorldPosition(Vector3f worldPosition)
{
	Vector3f pos;
	auto pChunk = GetChunkByWorldPosition(worldPosition);
	if ( pChunk )
	{
		return pChunk->GetBlockPositionByWorldPosition(worldPosition);
	}

	return pos;
}

BlockType CGameWorld::GetBlockByWorldPosition(Vector3f worldPosition)
{
	auto pChunk = GetChunkByWorldPosition(worldPosition);
	if ( pChunk )
	{
		return pChunk->GetBlockTypeByWorldPosition(worldPosition);
	}

	return BlockType::AIR;
}

// todo replace param vector with floats
Vector3f CGameWorld::GetNewPlayerPosition( Vector3f& playerWorldPosition )
{
	auto pChunk = GetChunkByWorldPosition(playerWorldPosition);
	if ( pChunk )
	{
		return pChunk->ValidatePhysicalPosition(playerWorldPosition);
	}

	return playerWorldPosition;

}

void CGameWorld::DrawFocusOnSelectedCube()
{
	if (m_bHasSelectedBlock )
	{
		m_pScene->SetGraphicsMode(false, false);
		BlockRenderer renderer;
		renderer.Prepare(NULL, BLOCK_SIZE, NULL);
		renderer.DrawFocusOnSelectedCube( m_SelectedBlockPosition );
		renderer.Finish();
		m_pScene->SetGraphicsMode(true, true);
	}
}



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

#include <stdint.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <inttypes.h>
#include "GameWorld.h"
#include "CFrustrum.h"
#include "../utils/Debug.h"


CGameWorld::CGameWorld( Basic3DScene* pScene ) : m_pScene(pScene)
{
	m_blockManager = new CBlockManager( pScene->GetTextureHandler() );
	m_blockManager->LoadBlocks();

	srand (time(NULL));

	m_pNoise = new PerlinNoise(.25, .15625, 1.5, 6.0, rand());

#ifdef DEBUG
	m_pChunkLogBuffer = new char[50];
	m_pDisplayListSizeLogBuffer = new char[50];
	m_pBlocksLogBuffer = new char[50];
	m_pFaceLogBuffer = new char[50];
	m_pSeedBuffer = new char[20];
#endif
}

CGameWorld::~CGameWorld()
{
#ifdef DEBUG
	delete[] m_pChunkLogBuffer;
	delete[] m_pDisplayListSizeLogBuffer;
	delete[] m_pBlocksLogBuffer;
	delete[] m_pFaceLogBuffer;
	delete[] m_pSeedBuffer;
#endif

	for (auto chunkEntry : m_ChunkList)
	{
		delete chunkEntry.first;
		delete chunkEntry.second;
	}
	m_ChunkList.clear();

	m_blockManager->UnloadBlocks();
	delete m_blockManager;
	delete m_pNoise;
}

void CGameWorld::GenerateWorld()
{
	for ( unsigned int x = 0; x < CHUNK_AMOUNT_X; x++)
	{
		for ( unsigned int z = 0; z < CHUNK_AMOUNT_Z; z++)
		{
			auto pChunk = new CChunk(*this);
			auto pPosition = new Vector3((float) (CHUNK_SIZE_X * x) + (CHUNK_SIZE_X / 2),  (float)CHUNK_SIZE_Y / 2, (float) (CHUNK_SIZE_Z * z) + (CHUNK_SIZE_Z / 2));
			m_ChunkList.insert(std::pair<Vector3*, CChunk*>( pPosition, pChunk ));
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
	Debug::GetInstance().Log( m_pChunkLogBuffer );

	sprintf(m_pSeedBuffer, "Seed: %d", m_pNoise->RandomSeed());
	Debug::GetInstance().Log( m_pSeedBuffer );

	//sprintf(m_pDisplayListSizeLogBuffer, "DisplayList size (MB): %d", displayListSize / 1024 / 1024);
	//Debug::getInstance().log( m_pDisplayListSizeLogBuffer );

	//ssprintf(m_pBlocksLogBuffer, "Blocks: %" PRId64 "/%" PRId64, activeBlocks, blocks);
	//sDebug::getInstance().log( m_pBlocksLogBuffer );

	//ssprintf(m_pFaceLogBuffer, "Faces: %" PRId64 "/%" PRId64, activeFaces, faces);
	//sDebug::getInstance().log( m_pFaceLogBuffer );
#endif
}

bool CGameWorld::ChunkInFov( Vector3& chunkPosition, Vector3& playerPosition, unsigned int fov)
{
	return (std::abs(chunkPosition.GetX() - playerPosition.GetX()) < CHUNK_SIZE_X * fov) &&
			(std::abs(chunkPosition.GetZ() - playerPosition.GetZ()) < CHUNK_SIZE_Z * fov);
}

CBlockManager& CGameWorld::GetBlockManager()
{
	return *m_blockManager;
}

CChunk* CGameWorld::GetChunkAt(const Vector3& centerPosition) const
{
	auto chunkIt = m_ChunkList.find(&centerPosition);
	if (chunkIt != m_ChunkList.end())
	{
		return chunkIt->second;
	}
	return NULL;
}

// todo replace param vector with floats
CChunk* CGameWorld::GetChunkByWorldPosition(const Vector3& worldPosition)
{
	unsigned int x = worldPosition.GetX() / CHUNK_SIZE_X;
	unsigned int z = worldPosition.GetZ() / CHUNK_SIZE_Z;

	Vector3 chunkCenterPosition((x * CHUNK_SIZE_X) + (CHUNK_SIZE_X / 2), CHUNK_SIZE_Y / 2, (z * CHUNK_SIZE_Z) + (CHUNK_SIZE_Z / 2));

	return GetChunkAt(chunkCenterPosition);
}

void CGameWorld::RemoveBlockByWorldPosition(const Vector3& blockPosition)
{
	auto pChunk = GetChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		pChunk->RemoveBlockByWorldPosition( blockPosition );
	}
}
void CGameWorld::AddBlockAtWorldPosition(const Vector3& blockPosition, BlockType type)
{
	auto pChunk = GetChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		pChunk->AddBlockByWorldPosition(blockPosition, type );
	}
}

void CGameWorld::UpdateFocusedBlockByWorldPosition( const Vector3& blockPosition )
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

Vector3 CGameWorld::GetBlockPositionByWorldPosition(const Vector3& worldPosition)
{
	Vector3 pos;
	auto pChunk = GetChunkByWorldPosition(worldPosition);
	if ( pChunk )
	{
		return pChunk->GetBlockPositionByWorldPosition(worldPosition);
	}

	return pos;
}

BlockType CGameWorld::GetBlockByWorldPosition(const Vector3& worldPosition)
{
	auto pChunk = GetChunkByWorldPosition(worldPosition);
	if ( pChunk )
	{
		return pChunk->GetBlockTypeByWorldPosition(worldPosition);
	}

	return BlockType::AIR;
}

// todo replace param vector with floats
Vector3 CGameWorld::GetNewPlayerPosition( const Vector3& playerWorldPosition )
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

const PerlinNoise& CGameWorld::GetNoise() const
{
	return *m_pNoise;
}



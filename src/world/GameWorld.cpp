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
#include "Frustrum.h"
#include "../renderer/MasterRenderer.h"
#include "../utils/Debug.h"



GameWorld::GameWorld()
{
    m_blockManager = new BlockManager();
	m_blockManager->LoadBlocks();

    srand (time(nullptr));
    m_pNoise = new PerlinNoise(.25, .15625, 1.5, 6.0, rand());
}

GameWorld::~GameWorld()
{
    for (auto chunkEntry : m_ChunkMap)
	{
		delete chunkEntry.first;
		delete chunkEntry.second;
	}
    m_ChunkMap.clear();

	m_blockManager->UnloadBlocks();
	delete m_blockManager;
	delete m_pNoise;
}

void GameWorld::GenerateWorld()
{
	for ( uint32_t x = 0; x < CHUNK_AMOUNT_X; x++)
	{
		for ( uint32_t z = 0; z < CHUNK_AMOUNT_Z; z++)
		{
            auto pChunk = new Chunk(*this);
			auto pPosition = new Vector3((CHUNK_BLOCK_SIZE_X * x) + (CHUNK_BLOCK_SIZE_X / 2), CHUNK_BLOCK_SIZE_Y / 2, (CHUNK_BLOCK_SIZE_Z * z) + (CHUNK_BLOCK_SIZE_Z / 2));
            m_ChunkMap.insert(std::pair<Vector3*, Chunk*>( pPosition, pChunk ));
			pChunk->Init( *pPosition );
		}
	}

    for (auto chunkEntry : m_ChunkMap)
	{
		chunkEntry.second->UpdateChunkNeighbors();
	}
}


void GameWorld::Draw()
{

#ifdef DEBUG
	uint32_t displayListSize = 0;
	uint64_t blocks = 0;
	uint64_t faces = 0;
	uint64_t activeFaces = 0;
	uint64_t activeBlocks = 0;
	uint32_t chunksInFrustrum = 0;
#endif

    auto& playerPosition = static_cast<Basic3DScene&>(Engine::Get().GetSceneHandler().GetCurrentScene()).GetEntityHandler().GetPlayer()->GetPosition();

    Frustrum::Instance().CalculateFrustum();

    for( auto& chunkEntry : m_ChunkMap)
	{
        auto& chunk = chunkEntry.second;
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
    LOG( "Rendered Chunks: %d/%d", chunksInFrustrum, m_ChunkMap.size() );
    LOG( "Seed: %d", m_pNoise->RandomSeed() );

    //LOG( "DisplayList size (MB): %d", displayListSize / 1024 / 1024 );

    //LOG( "Blocks: %" PRId64 "/%" PRId64, activeBlocks, blocks );

    //LOG(  "Faces: %" PRId64 "/%" PRId64, activeFaces, faces );
#endif
}

bool GameWorld::ChunkInFov( const Vector3& chunkPosition, const Vector3& playerPosition, uint32_t fov)
{
	return (std::abs(chunkPosition.GetX() - playerPosition.GetX()) < CHUNK_BLOCK_SIZE_X * fov) &&
			(std::abs(chunkPosition.GetZ() - playerPosition.GetZ()) < CHUNK_BLOCK_SIZE_Z * fov);
}

BlockManager& GameWorld::GetBlockManager()
{
	return *m_blockManager;
}

Chunk* GameWorld::GetChunkAt(const Vector3& centerPosition) const
{
    auto chunkIt = m_ChunkMap.find(&centerPosition);
    if (chunkIt != m_ChunkMap.end())
	{
		return chunkIt->second;
	}
    return nullptr;
}

Chunk* GameWorld::GetChunkByWorldPosition(const Vector3& worldPosition)
{
	uint32_t x = worldPosition.GetX() / CHUNK_BLOCK_SIZE_X;
	uint32_t z = worldPosition.GetZ() / CHUNK_BLOCK_SIZE_Z;

	Vector3 chunkCenterPosition((x * CHUNK_BLOCK_SIZE_X) + (CHUNK_BLOCK_SIZE_X / 2), CHUNK_BLOCK_SIZE_Y / 2, (z * CHUNK_BLOCK_SIZE_Z) + (CHUNK_BLOCK_SIZE_Z / 2));

	return GetChunkAt(chunkCenterPosition);
}

void GameWorld::RemoveBlockByWorldPosition(const Vector3& blockPosition)
{
	auto pChunk = GetChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		pChunk->RemoveBlockByWorldPosition( blockPosition );
	}
}
void GameWorld::AddBlockAtWorldPosition(const Vector3& blockPosition, BlockType type)
{
	auto pChunk = GetChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		pChunk->AddBlockByWorldPosition(blockPosition, type );
	}
}

void GameWorld::UpdateFocusedBlockByWorldPosition( const Vector3& blockPosition )
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

Vector3 GameWorld::GetBlockPositionByWorldPosition(const Vector3& worldPosition)
{
	auto pChunk = GetChunkByWorldPosition(worldPosition);
	if ( pChunk )
	{
		return pChunk->GetBlockPositionByWorldPosition(worldPosition);
	}

	return Vector3(0,0,0);
}

BlockType GameWorld::GetBlockByWorldPosition(const Vector3& worldPosition)
{
	auto pChunk = GetChunkByWorldPosition(worldPosition);
	if ( pChunk )
	{
		return pChunk->GetBlockTypeByWorldPosition(worldPosition);
	}

	return BlockType::AIR;
}

// todo replace param vector with floats
Vector3 GameWorld::GetNewPlayerPosition( const Vector3& playerWorldPosition )
{
	auto pChunk = GetChunkByWorldPosition(playerWorldPosition);
	if ( pChunk )
	{
		return pChunk->ValidatePhysicalPosition(playerWorldPosition);
	}

	return playerWorldPosition;
}

void GameWorld::DrawFocusOnSelectedCube()
{    
    if (m_bHasSelectedBlock )
	{
        MasterRenderer::SetGraphicsMode(false, false);
        BlockRenderer::DrawFocusOnSelectedCube( m_SelectedBlockPosition, BLOCK_SIZE_HALF );
        MasterRenderer::SetGraphicsMode(true, true);
    }
}

const PerlinNoise& GameWorld::GetNoise() const
{
	return *m_pNoise;
}



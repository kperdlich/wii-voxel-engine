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
#include "../utils/Filesystem.h"


GameWorld::GameWorld()
{    
    m_blockManager = new BlockManager();
	m_blockManager->LoadBlocks();    

    srand (time(nullptr));
    m_pNoise = new PerlinNoise(.25, .15625, 1.5, 6.0, rand());    
}

GameWorld::~GameWorld()
{
    LOG("Destroy world");
    for (auto chunkEntry : m_chunkMap)
	{
        //delete chunkEntry.first;
		delete chunkEntry.second;
	}
    m_chunkMap.clear();    

	m_blockManager->UnloadBlocks();
	delete m_blockManager;
	delete m_pNoise;

    LOG("World successfully destroyed");
}

void GameWorld::GenerateWorld()
{
    LOG("Create World");
	for ( uint32_t x = 0; x < CHUNK_AMOUNT_X; x++)
	{
		for ( uint32_t z = 0; z < CHUNK_AMOUNT_Z; z++)
		{
            auto pChunk = new Chunk(*this);
            Vector3 position((CHUNK_BLOCK_SIZE_X * x) + (CHUNK_BLOCK_SIZE_X / 2), CHUNK_BLOCK_SIZE_Y / 2, (CHUNK_BLOCK_SIZE_Z * z) + (CHUNK_BLOCK_SIZE_Z / 2));
            m_chunkMap.insert(std::pair<Vector3, Chunk*>(position, pChunk ));
            pChunk->Init( position );
		}
	}

    for (auto& chunkEntry : m_chunkMap)
	{
		chunkEntry.second->UpdateChunkNeighbors();
    }

    LOG("World created with %d chunks", m_chunkMap.size());
}


void GameWorld::Draw()
{
    auto& playerPosition = static_cast<Basic3DScene&>(Engine::Get().GetSceneHandler().GetCurrentScene()).GetEntityHandler().GetPlayer()->GetPosition();

    //Frustrum::Instance().CalculateFrustum();

    for( auto& chunkEntry : m_chunkMap)
	{
        Chunk* chunk = chunkEntry.second;
        auto& chunkPosition = chunk->GetCenterPosition();

        if ( ChunkInFov(chunkPosition, playerPosition, CHUNK_PLAYER_FOV) )
        {
            if ( chunk->IsDirty() )
            {
                chunk->RebuildDisplayList();
            }
            chunk->Render();
        }
        else
        {
            chunk->DeleteDisplayList();
        }
	}

	DrawFocusOnSelectedCube();
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
    auto chunkIt = m_chunkMap.find(centerPosition);
    if (chunkIt != m_chunkMap.end())
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

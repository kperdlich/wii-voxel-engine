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
#include "chunk/chunkserializer.h"


GameWorld::GameWorld()
{    
    m_blockManager = new BlockManager();
    m_blockManager->LoadBlocks();

    m_chunkLoader = new ChunkLoader();

    srand (time(nullptr));
    m_pNoise = new PerlinNoise(.25, .1, .5, 6.0, rand());
}

GameWorld::~GameWorld()
{
    LOG("Destroy world");    
    m_chachedChunkMap.clear();

    delete m_chunkLoader;

	m_blockManager->UnloadBlocks();
	delete m_blockManager;
	delete m_pNoise;    
}

void GameWorld::GenerateWorld()
{
    auto& playerPosition = static_cast<Basic3DScene&>(Engine::Get().GetSceneHandler().GetCurrentScene()).GetEntityHandler().GetPlayer()->GetPosition();
    m_chunkLoader->Init(playerPosition, this);   
    /*for ( uint32_t x = 0; x < CHUNK_AMOUNT_X; x++)
	{
		for ( uint32_t z = 0; z < CHUNK_AMOUNT_Z; z++)
		{
            auto pChunk = new Chunk(*this);
            Vector3 position((CHUNK_BLOCK_SIZE_X * x) + (CHUNK_BLOCK_SIZE_X / 2), CHUNK_BLOCK_SIZE_Y / 2, (CHUNK_BLOCK_SIZE_Z * z) + (CHUNK_BLOCK_SIZE_Z / 2));
            m_chachedChunkMap.insert(std::pair<Vector3, Chunk*>(position, pChunk ));
            pChunk->Init();
            pChunk->Build(position);
        }
	}    

    for (auto& chunkEntry : m_chachedChunkMap)
	{
		chunkEntry.second->UpdateChunkNeighbors();
    }*/    
}


void GameWorld::Draw()
{
    auto& playerPosition = static_cast<Basic3DScene&>(Engine::Get().GetSceneHandler().GetCurrentScene()).GetEntityHandler().GetPlayer()->GetPosition();
    auto loadedChunks = m_chunkLoader->GetLoadedChunks();
    for( auto& chunk : loadedChunks)
    {        
        if (chunk->IsDirty())
        {             
            chunk->RebuildDisplayList();            
        }
        chunk->Render();
    }
    m_chunkLoader->UpdateChunksBy(playerPosition);    
    DrawFocusOnSelectedCube();

    /*for( auto& chunkEntry : m_chachedChunkMap)
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
    DrawFocusOnSelectedCube();*/
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
    return m_chunkLoader->GetChunkFromCash(centerPosition);
}

Chunk* GameWorld::GetCashedChunkByWorldPosition(const Vector3& worldPosition)
{
    return m_chunkLoader->GetCashedChunkByWorldPosition(worldPosition);
}

void GameWorld::RemoveBlockByWorldPosition(const Vector3& blockPosition)
{
    auto pChunk = GetCashedChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		pChunk->RemoveBlockByWorldPosition( blockPosition );
	}
}
void GameWorld::AddBlockAtWorldPosition(const Vector3& blockPosition, BlockType type)
{
    auto pChunk = GetCashedChunkByWorldPosition(blockPosition);
	if ( pChunk )
	{
		pChunk->AddBlockByWorldPosition(blockPosition, type );
	}
}

void GameWorld::UpdateFocusedBlockByWorldPosition( const Vector3& blockPosition )
{
    auto pChunk = GetCashedChunkByWorldPosition(blockPosition);
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
    auto pChunk = GetCashedChunkByWorldPosition(worldPosition);
	if ( pChunk )
	{
		return pChunk->GetBlockPositionByWorldPosition(worldPosition);
	}

	return Vector3(0,0,0);
}

BlockType GameWorld::GetBlockByWorldPosition(const Vector3& worldPosition)
{
    auto pChunk = GetCashedChunkByWorldPosition(worldPosition);
	if ( pChunk )
	{
		return pChunk->GetBlockTypeByWorldPosition(worldPosition);
	}

	return BlockType::AIR;
}

Vector3 GameWorld::GetNewPlayerPosition( const Vector3& playerWorldPosition )
{
    auto pChunk = GetCashedChunkByWorldPosition(playerWorldPosition);
	if ( pChunk )
    {
        return pChunk->GetPhysicalPosition(playerWorldPosition);
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

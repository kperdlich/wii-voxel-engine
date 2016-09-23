/*
 * Chunk.cpp
 *
 *  Created on: 13.07.2016
 *      Author: Kevin
 */

#include <cstdlib>
#include "Chunk.h"
#include "../blocks/BlockRenderer.h"
#include "../../../utils/Debug.h"

CChunk::CChunk(class CGameWorld& gameWorld) : m_IsDirty(true)
{
	m_pWorldManager = &gameWorld;
}

CChunk::~CChunk()
{
	DeleteDisplayList();
	ClearBlockRenderList();

	for (int x = 0; x < CHUNK_SIZE_X; ++x)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; ++y)
		{
			delete [] m_pBlocks[x][y];
		}

		delete [] m_pBlocks[x];
	}
	delete [] m_pBlocks;
}

void CChunk::Init(Vector3f& position)
{
	m_pCenterPosition = &position;

	m_pBlocks = new BlockType**[CHUNK_SIZE_X];
	for (unsigned int x = 0; x < CHUNK_SIZE_X; x++)
	{
		m_pBlocks[x] = new BlockType*[CHUNK_SIZE_Y];

		for (unsigned int y = 0; y < CHUNK_SIZE_Y; y++)
		{
			m_pBlocks[x][y] = new BlockType[CHUNK_SIZE_Z];
		}
	}

	for ( unsigned int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for ( unsigned int y = 0; y < CHUNK_SIZE_Y; y++ )
		{
			for ( unsigned int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				BlockType blockType = BlockType::AIR;
				if ( y < CHUNK_SIZE_Y - 3)
				{
					blockType = BlockType::DIRT;
				}
				else if ( y == CHUNK_SIZE_Y - 3 )
				{
					blockType = BlockType::GRASS;
				}
				m_pBlocks[x][y][z] = blockType;
			}
		}
	}
}

void CChunk::UpdateChunkNeighbors()
{
	Vector3f leftChunkPos(m_pCenterPosition->GetX() - CHUNK_SIZE_X, m_pCenterPosition->GetY(), m_pCenterPosition->GetZ());
	Vector3f rightChunkPos(m_pCenterPosition->GetX() + CHUNK_SIZE_X, m_pCenterPosition->GetY(), m_pCenterPosition->GetZ());
	Vector3f frontChunkPos(m_pCenterPosition->GetX(), m_pCenterPosition->GetY(), m_pCenterPosition->GetZ() + CHUNK_SIZE_Z);
	Vector3f backChunkPos(m_pCenterPosition->GetX(), m_pCenterPosition->GetY(), m_pCenterPosition->GetZ() - CHUNK_SIZE_X);

	m_pChunkLeft = m_pWorldManager->GetChunkAt(leftChunkPos);
	m_pChunkRight = m_pWorldManager->GetChunkAt(rightChunkPos);
	m_pChunkFront = m_pWorldManager->GetChunkAt(frontChunkPos);
	m_pChunkBack = m_pWorldManager->GetChunkAt(backChunkPos);
}


void CChunk::Render()
{
	if ( m_DisplayListSize > 0 )
	{
		GX_CallDispList(m_DispList, m_DisplayListSize);
	}
}

bool CChunk::AddBlockToRenderList(BlockType type, BlockRenderData& blockRenderData)
{
	bool bSuccessful = false;
	auto blockRenderListIt = m_mBlockRenderList.find(type);
	if (blockRenderListIt != m_mBlockRenderList.end())
	{
		blockRenderListIt->second.push_back(&blockRenderData);
		bSuccessful = true;
	}
	else
	{
		std::vector<BlockRenderData*> blockList;
		blockList.push_back(&blockRenderData);
		m_mBlockRenderList.insert(std::pair<BlockType, std::vector<BlockRenderData*> >(type, blockList ));
		bSuccessful = true;
	}

	return bSuccessful;
}

bool CChunk::IsBlockVisible(uint32_t iX, uint32_t iY, uint32_t iZ, BlockFaceVisibiltyData* &pFaceData)
{

	BlockFaceVisibiltyData localFaceData;
	bool isVisible = false;
	bool bIsAir = m_pBlocks[iX][iY][iZ] == BlockType::AIR;

	if ( iX == 0 )
	{
		if (bIsAir)
		{
			if ( !m_bNeighbourUpdate && m_pChunkLeft && m_pChunkLeft->m_pBlocks[CHUNK_SIZE_X -1][iY][iZ] != BlockType::AIR)
			{
				m_pChunkLeft->SetDirty(true); //rebuild neighbour
				m_pChunkLeft->m_bNeighbourUpdate = true;
			}
		}
		else if ( !m_pChunkLeft || (m_pChunkLeft && m_pChunkLeft->m_pBlocks[CHUNK_SIZE_X -1][iY][iZ] == BlockType::AIR))
		{
			localFaceData.bLeftFace = true;
			localFaceData.faces++;
			isVisible = true;
		}
	}

	if ( iX == CHUNK_SIZE_X -1 )
	{
		if (bIsAir)
		{
			if ( !m_bNeighbourUpdate && m_pChunkRight && m_pChunkRight->m_pBlocks[0][iY][iZ] != BlockType::AIR)
			{
				m_pChunkRight->SetDirty(true); //rebuild neighbour
				m_pChunkRight->m_bNeighbourUpdate = true;
			}
		}
		else if ( !m_pChunkRight || (m_pChunkRight && m_pChunkRight->m_pBlocks[0][iY][iZ] == BlockType::AIR))
		{
			localFaceData.bRightFace = true;
			localFaceData.faces++;
			isVisible = true;
		}
	}

	if ( iZ == 0 )
	{
		if (bIsAir)
		{
			if ( !m_bNeighbourUpdate && m_pChunkBack && m_pChunkBack->m_pBlocks[iX][iY][CHUNK_SIZE_Z -1] != BlockType::AIR)
			{
				m_pChunkBack->SetDirty(true); //rebuild neighbour
				m_pChunkBack->m_bNeighbourUpdate = true;
			}
		}
		else if (!m_pChunkBack || (m_pChunkBack && m_pChunkBack->m_pBlocks[iX][iY][CHUNK_SIZE_Z -1] == BlockType::AIR))
		{
			localFaceData.bBackFace = true;
			localFaceData.faces++;
			isVisible = true;
		}
	}

	if (iZ == CHUNK_SIZE_Z -1 )
	{
		if (bIsAir)
		{
			if ( !m_bNeighbourUpdate && m_pChunkFront && m_pChunkFront->m_pBlocks[iX][iY][0] != BlockType::AIR)
			{
				m_pChunkFront->SetDirty(true); //rebuild neighbour
				m_pChunkFront->m_bNeighbourUpdate = true;
			}
		}
		else if ( !m_pChunkFront || (m_pChunkFront && m_pChunkFront->m_pBlocks[iX][iY][0] == BlockType::AIR))
		{
			localFaceData.bFrontFace = true;
			localFaceData.faces++;
			isVisible = true;
		}
	}

	if ( !bIsAir )
	{
		if ( iY == CHUNK_SIZE_Y -1 )
		{
			localFaceData.bTopFace = true;
			localFaceData.faces++;
			isVisible = true;
		}

		 // Check all 6 block faces if neighbor is air
		if ( iX + 1 <= CHUNK_SIZE_X -1 && m_pBlocks[iX + 1][iY][iZ] == BlockType::AIR)
		{
			localFaceData.bRightFace = true;
			localFaceData.faces++;
			isVisible = true;
		}

		if ( iX > 0 && m_pBlocks[iX - 1][iY][iZ] == BlockType::AIR)
		{
			localFaceData.bLeftFace = true;
			localFaceData.faces++;
			isVisible = true;
		}

		if ( iY + 1 <= CHUNK_SIZE_Y -1 && m_pBlocks[iX][iY + 1][iZ] == BlockType::AIR)
		{
			localFaceData.bTopFace = true;
			localFaceData.faces++;
			isVisible = true;
		}


		if (iY > 0 && m_pBlocks[iX][iY - 1][iZ] == BlockType::AIR)
		{
			localFaceData.bBottomFace = true;
			localFaceData.faces++;
			isVisible = true;
		}

		if ( iZ + 1 <= CHUNK_SIZE_Z -1 && m_pBlocks[iX][iY][iZ + 1] == BlockType::AIR)
		{
			localFaceData.bFrontFace = true;
			localFaceData.faces++;
			isVisible = true;
		}

		if ( iZ > 0 && m_pBlocks[iX][iY][iZ - 1] == BlockType::AIR)
		{
			localFaceData.bBackFace = true;
			localFaceData.faces++;
			isVisible = true;
		}

		if (isVisible)
		{
			pFaceData = new BlockFaceVisibiltyData();
			pFaceData->bBackFace = localFaceData.bBackFace;
			pFaceData->bBottomFace = localFaceData.bBottomFace;
			pFaceData->bFrontFace = localFaceData.bFrontFace;
			pFaceData->bLeftFace = localFaceData.bLeftFace;
			pFaceData->bRightFace = localFaceData.bRightFace;
			pFaceData->bTopFace = localFaceData.bTopFace;
			pFaceData->faces = localFaceData.faces;
		}
	}

	return isVisible;
}

void CChunk::BuildBlockRenderList()
{
	m_AmountOfBlocks = 0;
	m_AmountOfFaces = 0;

	for ( unsigned int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for ( unsigned int y = 0; y < CHUNK_SIZE_Y; y++ )
		{
			for ( unsigned int z = 0; z < CHUNK_SIZE_Z; z++)
			{
				BlockFaceVisibiltyData* pFaceData = NULL;

				if ( IsBlockVisible(x, y, z, pFaceData))
				{
					BlockRenderData* renderData = new BlockRenderData();
					renderData->pFaceData = pFaceData;
					renderData->pBlockPosition = new Vector3f( (m_pCenterPosition->GetX() - (CHUNK_SIZE_X / 2) + (x * BLOCK_SIZE * 2)), (m_pCenterPosition->GetY() - (CHUNK_SIZE_Y / 2) + (y * BLOCK_SIZE * 2)), (m_pCenterPosition->GetZ() - (CHUNK_SIZE_Z / 2) + (z * BLOCK_SIZE * 2)));
					AddBlockToRenderList(m_pBlocks[x][y][z], *renderData);
					m_AmountOfBlocks++;
					m_AmountOfFaces += pFaceData->faces;
				}
			}
		}
	}
}

void CChunk::ClearBlockRenderList()
{
	for(auto renderListIt = m_mBlockRenderList.begin(); renderListIt != m_mBlockRenderList.end(); ++renderListIt)
	{
		for(auto blockIt = renderListIt->second.begin(); blockIt != renderListIt->second.end(); ++blockIt)
		{
			delete ((*blockIt)->pFaceData);
			delete ((*blockIt)->pBlockPosition);
			delete (*blockIt);
		}
	}

	m_mBlockRenderList.clear();
}


void CChunk::CreateDisplayList(size_t sizeOfDisplayList)
{
	m_DispList = memalign(32, sizeOfDisplayList);
	memset(m_DispList, 0, sizeOfDisplayList);
	DCInvalidateRange(m_DispList, sizeOfDisplayList);
	GX_BeginDispList(m_DispList, sizeOfDisplayList);
}

void CChunk::FinishDisplayList()
{
	m_DisplayListSize = GX_EndDispList();
	m_IsDirty = false;
}


bool CChunk::IsDirty()
{
	return m_IsDirty;
}

void CChunk::SetDirty(bool dirty)
{
	m_IsDirty = dirty;
}

unsigned int CChunk::GetDisplayListSize()
{
	return m_DisplayListSize;
}


uint64_t CChunk::GetAmountOfBlocks()
{
	return m_AmountOfBlocks;
}

uint64_t CChunk::GetAmountOfFaces()
{
	return m_AmountOfFaces;
}

Vector3f& CChunk::GetCenterPosition()
{
	return *m_pCenterPosition;
}

void CChunk::DeleteDisplayList()
{
	if ( m_DisplayListSize > 0 )
	{
		free(m_DispList);
		m_DisplayListSize = 0;
		m_DispList = NULL;
		m_IsDirty = true;
	}
}

void CChunk::RebuildDisplayList()
{
	BlockRenderer blockRenderer;

	ClearBlockRenderList();
	BuildBlockRenderList();

	DeleteDisplayList();
	CreateDisplayList( size_t((32 * 6) * m_AmountOfFaces) ); // 32 * 6 magic numbers, seems to work fine

	for(auto it = m_mBlockRenderList.begin(); it != m_mBlockRenderList.end(); ++it)
	{
		auto pBlockToRender = m_pWorldManager->GetBlockManager().GetBlockByType(it->first);
		blockRenderer.Prepare( &it->second, pBlockToRender->getSize(), pBlockToRender->GetTexture());
		blockRenderer.Rebuild();
	}

	blockRenderer.Finish();

	FinishDisplayList();
	ClearBlockRenderList();

	m_bNeighbourUpdate = false;
}

void CChunk::RemoveBlockByWorldPosition(Vector3f blockPosition)
{
	unsigned int x,y,z;

	GetLocalBlockPositionByWorldPosition(blockPosition, &x, &y, &z);

	m_pBlocks[x][y][z] = BlockType::AIR;

	m_IsDirty = true;
}

void CChunk::AddBlockByWorldPosition(Vector3f blockPosition, BlockType type)
{
	unsigned int x,y,z;
	GetLocalBlockPositionByWorldPosition(blockPosition, &x, &y, &z);

	if ( m_pBlocks[x][y][z] == BlockType::AIR)
	{
		 m_pBlocks[x][y][z] = type;
		 m_IsDirty = true;
	}
}

void CChunk::GetLocalBlockPositionByWorldPosition(Vector3f& blockWorldPosition, unsigned int* x, unsigned int* y, unsigned int* z)
{
	*x = (unsigned int) blockWorldPosition.GetX() % (unsigned int) CHUNK_SIZE_X;
	*y = (unsigned int) blockWorldPosition.GetY() % (unsigned int) CHUNK_SIZE_Y;
	*z = (unsigned int) blockWorldPosition.GetZ() % (unsigned int) CHUNK_SIZE_Z;
}

Vector3f CChunk::GetBlockPositionByWorldPosition(Vector3f& worldPosition)
{
	unsigned int x,y,z;
	GetLocalBlockPositionByWorldPosition(worldPosition, &x, &y, &z);

	return Vector3f( (m_pCenterPosition->GetX() - (CHUNK_SIZE_X / 2) + (x * BLOCK_SIZE * 2)), (m_pCenterPosition->GetY() - (CHUNK_SIZE_Y / 2) + (y * BLOCK_SIZE * 2)), (m_pCenterPosition->GetZ() - (CHUNK_SIZE_Z / 2) + (z * BLOCK_SIZE * 2)));
}

BlockType CChunk::GetBlockTypeByWorldPosition(Vector3f& worldPosition)
{
	unsigned int x,y,z;
	GetLocalBlockPositionByWorldPosition(worldPosition, &x, &y, &z);
	return m_pBlocks[x][y][z];
}

Vector3f CChunk::ValidatePhysicalPosition(Vector3f& position)
{
	Vector3f pos = GetBlockPositionByWorldPosition(position);

	for ( unsigned int i = CHUNK_SIZE_Y - 1; i > 1; i--)
	{
		pos.SetY(i);
		if ( GetBlockTypeByWorldPosition(pos) != BlockType::AIR )
		{
			break;
		}
	}

	return pos;
}

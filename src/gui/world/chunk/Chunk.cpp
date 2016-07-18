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
				BlockType blockType = x % 2 == 0 ? BlockType::DIRT : BlockType::GRASS;
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

	m_bChunkLeft = m_pWorldManager->GetChunkAt(leftChunkPos);
	m_bChunkRight = m_pWorldManager->GetChunkAt(rightChunkPos);
	m_bChunkFront = m_pWorldManager->GetChunkAt(frontChunkPos);
	m_bChunkBack = m_pWorldManager->GetChunkAt(backChunkPos);
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

	m_IsDirty = true;

	return bSuccessful;
}

bool CChunk::IsBlockVisible(uint32_t iX, uint32_t iY, uint32_t iZ, BlockFaceVisibiltyData* &pFaceData)
{

	BlockFaceVisibiltyData localFaceData;
	bool isVisible = false;

	if ( m_pBlocks[iX][iY][iZ] != BlockType::AIR )
	{
		if ( iX == 0 && !m_bChunkLeft)
		{
			localFaceData.LeftFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}

		if ( iX == CHUNK_SIZE_X -1 && !m_bChunkRight)
		{
			localFaceData.RightFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}

		if ( iZ == 0 && !m_bChunkBack)
		{
			localFaceData.BackFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}

		if (iZ == CHUNK_SIZE_Z -1 && !m_bChunkFront)
		{
			localFaceData.FrontFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}

		if ( iY == CHUNK_SIZE_Y -1 )
		{
			localFaceData.TopFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}


		 // Check all 6 block faces if neighbor is air
		if ( iX + 1 <= CHUNK_SIZE_X -1 && m_pBlocks[iX + 1][iY][iZ] == BlockType::AIR)
		{
			localFaceData.RightFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}

		if ( iX > 0 && m_pBlocks[iX - 1][iY][iZ] == BlockType::AIR)
		{
			localFaceData.LeftFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}

		if ( iY + 1 <= CHUNK_SIZE_Y -1 && m_pBlocks[iX][iY + 1][iZ] == BlockType::AIR)
		{
			localFaceData.TopFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}


		if (iY > 0 && m_pBlocks[iX][iY - 1][iZ] == BlockType::AIR)
		{
			localFaceData.BottomFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}

		if ( iZ + 1 <= CHUNK_SIZE_Z -1 && m_pBlocks[iX][iY][iZ + 1] == BlockType::AIR)
		{
			localFaceData.FrontFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}

		if ( iZ > 0 && m_pBlocks[iX][iY][iZ - 1] == BlockType::AIR)
		{
			localFaceData.BackFace = true;
			localFaceData.Faces++;
			isVisible = true;
		}


		if (isVisible)
		{
			pFaceData = new BlockFaceVisibiltyData();
			pFaceData->BackFace = localFaceData.BackFace;
			pFaceData->BottomFace = localFaceData.BottomFace;
			pFaceData->FrontFace = localFaceData.FrontFace;
			pFaceData->LeftFace = localFaceData.LeftFace;
			pFaceData->RightFace = localFaceData.RightFace;
			pFaceData->TopFace = localFaceData.TopFace;
			pFaceData->Faces = localFaceData.Faces;
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
					renderData->FaceData = pFaceData;
					renderData->BlockPosition = new Vector3f( (m_pCenterPosition->GetX() - (CHUNK_SIZE_X / 2) + (x * BLOCK_SIZE * 2)), (m_pCenterPosition->GetY() - (CHUNK_SIZE_Y / 2) + (y * BLOCK_SIZE * 2)), (m_pCenterPosition->GetZ() - (CHUNK_SIZE_Z / 2) + (z * BLOCK_SIZE * 2)));
					AddBlockToRenderList(m_pBlocks[x][y][z], *renderData);
					m_AmountOfBlocks++;
					m_AmountOfFaces += pFaceData->Faces;
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
			delete ((*blockIt)->FaceData);
			delete ((*blockIt)->BlockPosition);
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
	free(m_DispList);
	m_DisplayListSize = 0;
	m_DispList = NULL;
	m_IsDirty = true;
}

void CChunk::RebuildDisplayList()
{
	auto pBlockRender = new BlockRenderer();

	ClearBlockRenderList();
	BuildBlockRenderList();

	CreateDisplayList( size_t((32 * 6) * m_AmountOfFaces) ); // 32 * 6 magic numbers, seems to work fine

	for(auto it = m_mBlockRenderList.begin(); it != m_mBlockRenderList.end(); ++it)
	{
		auto pBlockToRender = m_pWorldManager->GetBlockManager().GetBlockByType(it->first);
		pBlockRender->Prepare( &it->second, pBlockToRender->getSize(), pBlockToRender->GetTexture());
		pBlockRender->Rebuild();
	}

	pBlockRender->Finish();

	FinishDisplayList();
	ClearBlockRenderList();

	delete pBlockRender;
}

void CChunk::RemoveBlockByWorldPosition(Vector3f blockPosition)
{
	unsigned int x = (unsigned int) blockPosition.GetX() % (unsigned int) CHUNK_SIZE_X;
	unsigned int y = (unsigned int) blockPosition.GetY() % (unsigned int) CHUNK_SIZE_Y;
	unsigned int z = (unsigned int) blockPosition.GetZ() % (unsigned int) CHUNK_SIZE_Z;

	m_pBlocks[x][y][z] = BlockType::AIR;

	m_IsDirty = true;
}


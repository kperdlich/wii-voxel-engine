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

#include <cstdlib>
#include "Chunk.h"
#include "../../utils/CRenderHelper.h"
#include "../../renderer/BlockRenderer.h"
#include "../../utils/Debug.h"

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

bool CChunk::AddBlockToRenderList(BlockType type, const BlockRenderVO& blockRenderVO)
{
	bool bSuccessful = false;
	auto blockRenderListIt = m_mBlockRenderList.find(type);
	if (blockRenderListIt != m_mBlockRenderList.end())
	{
		blockRenderListIt->second.push_back(&blockRenderVO);
		bSuccessful = true;
	}
	else
	{
		std::vector<const BlockRenderVO*> blockList;
		blockList.push_back(&blockRenderVO);
		m_mBlockRenderList.insert(std::pair<BlockType, std::vector<const BlockRenderVO*> >(type, blockList ));
		bSuccessful = true;
	}

	return bSuccessful;
}

bool CChunk::IsBlockVisible(uint32_t iX, uint32_t iY, uint32_t iZ, BlockFaceVisibiltyVO* &pFaceVO)
{

	BlockFaceVisibiltyVO localFaceVO;
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
			localFaceVO.bLeftFace = true;
			localFaceVO.faces++;
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
			localFaceVO.bRightFace = true;
			localFaceVO.faces++;
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
			localFaceVO.bBackFace = true;
			localFaceVO.faces++;
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
			localFaceVO.bFrontFace = true;
			localFaceVO.faces++;
			isVisible = true;
		}
	}

	if ( !bIsAir )
	{
		if ( iY == CHUNK_SIZE_Y -1 )
		{
			localFaceVO.bTopFace = true;
			localFaceVO.faces++;
			isVisible = true;
		}

		 // Check all 6 block faces if neighbor is air
		if ( iX + 1 <= CHUNK_SIZE_X -1 && m_pBlocks[iX + 1][iY][iZ] == BlockType::AIR)
		{
			localFaceVO.bRightFace = true;
			localFaceVO.faces++;
			isVisible = true;
		}

		if ( iX > 0 && m_pBlocks[iX - 1][iY][iZ] == BlockType::AIR)
		{
			localFaceVO.bLeftFace = true;
			localFaceVO.faces++;
			isVisible = true;
		}

		if ( iY + 1 <= CHUNK_SIZE_Y -1 && m_pBlocks[iX][iY + 1][iZ] == BlockType::AIR)
		{
			localFaceVO.bTopFace = true;
			localFaceVO.faces++;
			isVisible = true;
		}


		if (iY > 0 && m_pBlocks[iX][iY - 1][iZ] == BlockType::AIR)
		{
			localFaceVO.bBottomFace = true;
			localFaceVO.faces++;
			isVisible = true;
		}

		if ( iZ + 1 <= CHUNK_SIZE_Z -1 && m_pBlocks[iX][iY][iZ + 1] == BlockType::AIR)
		{
			localFaceVO.bFrontFace = true;
			localFaceVO.faces++;
			isVisible = true;
		}

		if ( iZ > 0 && m_pBlocks[iX][iY][iZ - 1] == BlockType::AIR)
		{
			localFaceVO.bBackFace = true;
			localFaceVO.faces++;
			isVisible = true;
		}

		if (isVisible)
		{
			pFaceVO = new BlockFaceVisibiltyVO();
			pFaceVO->bBackFace = localFaceVO.bBackFace;
			pFaceVO->bBottomFace = localFaceVO.bBottomFace;
			pFaceVO->bFrontFace = localFaceVO.bFrontFace;
			pFaceVO->bLeftFace = localFaceVO.bLeftFace;
			pFaceVO->bRightFace = localFaceVO.bRightFace;
			pFaceVO->bTopFace = localFaceVO.bTopFace;
			pFaceVO->faces = localFaceVO.faces;
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
				BlockFaceVisibiltyVO* pFaceVO = NULL;

				if ( IsBlockVisible(x, y, z, pFaceVO))
				{
					BlockRenderVO* renderVO = new BlockRenderVO();
					renderVO->pFaceVO = pFaceVO;
					renderVO->pBlockPosition = new Vector3f( (m_pCenterPosition->GetX() - (CHUNK_SIZE_X / 2) + (x * BLOCK_SIZE * 2)), (m_pCenterPosition->GetY() - (CHUNK_SIZE_Y / 2) + (y * BLOCK_SIZE * 2)), (m_pCenterPosition->GetZ() - (CHUNK_SIZE_Z / 2) + (z * BLOCK_SIZE * 2)));
					AddBlockToRenderList(m_pBlocks[x][y][z], *renderVO);
					m_AmountOfBlocks++;
					m_AmountOfFaces += pFaceVO->faces;
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
			delete ((*blockIt)->pFaceVO);
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

unsigned int CChunk::GetDisplayListSize() const
{
	return m_DisplayListSize;
}


uint64_t CChunk::GetAmountOfBlocks() const
{
	return m_AmountOfBlocks;
}

uint64_t CChunk::GetAmountOfFaces() const
{
	return m_AmountOfFaces;
}

const Vector3f& CChunk::GetCenterPosition() const
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
	CreateDisplayList( CRenderHelper::GetDisplayListSizeForFaces(m_AmountOfFaces) );

	for(auto it = m_mBlockRenderList.begin(); it != m_mBlockRenderList.end(); ++it)
	{
		auto pBlockToRender = m_pWorldManager->GetBlockManager().GetBlockByType(it->first);
		blockRenderer.Prepare( &it->second, pBlockToRender->GetSize(), pBlockToRender->GetTexture());
		blockRenderer.Rebuild();
	}

	blockRenderer.Finish();

	FinishDisplayList();
	ClearBlockRenderList();

	m_bNeighbourUpdate = false;
}

void CChunk::RemoveBlockByWorldPosition(const Vector3f& blockPosition)
{
	unsigned int x,y,z;

	GetLocalBlockPositionByWorldPosition(blockPosition, &x, &y, &z);

	m_pBlocks[x][y][z] = BlockType::AIR;

	m_IsDirty = true;
}

void CChunk::AddBlockByWorldPosition(const Vector3f& blockPosition, BlockType type)
{
	unsigned int x,y,z;
	GetLocalBlockPositionByWorldPosition(blockPosition, &x, &y, &z);

	if ( m_pBlocks[x][y][z] == BlockType::AIR)
	{
		 m_pBlocks[x][y][z] = type;
		 m_IsDirty = true;
	}
}

void CChunk::GetLocalBlockPositionByWorldPosition(const Vector3f& blockWorldPosition, unsigned int* x, unsigned int* y, unsigned int* z) const
{
	*x = (unsigned int) blockWorldPosition.GetX() % (unsigned int) CHUNK_SIZE_X;
	*y = (unsigned int) blockWorldPosition.GetY() % (unsigned int) CHUNK_SIZE_Y;
	*z = (unsigned int) blockWorldPosition.GetZ() % (unsigned int) CHUNK_SIZE_Z;
}

Vector3f CChunk::GetBlockPositionByWorldPosition(const Vector3f& worldPosition) const
{
	unsigned int x,y,z;
	GetLocalBlockPositionByWorldPosition(worldPosition, &x, &y, &z);

	return Vector3f( (m_pCenterPosition->GetX() - (CHUNK_SIZE_X / 2) + (x * BLOCK_SIZE * 2)), (m_pCenterPosition->GetY() - (CHUNK_SIZE_Y / 2) + (y * BLOCK_SIZE * 2)), (m_pCenterPosition->GetZ() - (CHUNK_SIZE_Z / 2) + (z * BLOCK_SIZE * 2)));
}

BlockType CChunk::GetBlockTypeByWorldPosition(const Vector3f& worldPosition) const
{
	unsigned int x,y,z;
	GetLocalBlockPositionByWorldPosition(worldPosition, &x, &y, &z);
	return m_pBlocks[x][y][z];
}

Vector3f CChunk::ValidatePhysicalPosition(const Vector3f& position) const
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

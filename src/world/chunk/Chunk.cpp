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


#include "Chunk.h"
#include "../PerlinNoise.h"
#include "../../utils/MathHelper.h"
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

void CChunk::Init(Vector3& position)
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

	const PerlinNoise& pn = m_pWorldManager->GetNoise();

	for ( unsigned int x = 0; x < CHUNK_SIZE_X; x++)
	{
		for ( unsigned int z = 0; z < CHUNK_SIZE_Z; z++)
		{
			for ( unsigned int y = 0; y < CHUNK_SIZE_Y; y++)
			{
				m_pBlocks[x][y][z] = BlockType::AIR;
			}

			double xWorld, zWorld;
			xWorld = (m_pCenterPosition->GetX() - (CHUNK_BLOCK_SIZE_X / 2) + (x * BLOCK_SIZE));
			zWorld = (m_pCenterPosition->GetZ() - (CHUNK_BLOCK_SIZE_Z / 2) + (z * BLOCK_SIZE));

			double noise = pn.GetHeight(xWorld, zWorld);
			unsigned int height = (unsigned int) MathHelper::Clamp(CHUNK_SIZE_Y * noise, 1.0, CHUNK_SIZE_Y);

			for (unsigned int y = 0; y < height; y++)
			{
				if ( y == height - 1 )
				{
					m_pBlocks[x][y][z] = BlockType::GRASS;
				}
				else
				{
					m_pBlocks[x][y][z] = BlockType::DIRT;
				}
			}
		}
	}
}

void CChunk::UpdateChunkNeighbors()
{
	Vector3 leftChunkPos(m_pCenterPosition->GetX() - CHUNK_BLOCK_SIZE_X, m_pCenterPosition->GetY(), m_pCenterPosition->GetZ());
	Vector3 rightChunkPos(m_pCenterPosition->GetX() + CHUNK_BLOCK_SIZE_X, m_pCenterPosition->GetY(), m_pCenterPosition->GetZ());
	Vector3 frontChunkPos(m_pCenterPosition->GetX(), m_pCenterPosition->GetY(), m_pCenterPosition->GetZ() + CHUNK_BLOCK_SIZE_Z);
	Vector3 backChunkPos(m_pCenterPosition->GetX(), m_pCenterPosition->GetY(), m_pCenterPosition->GetZ() - CHUNK_BLOCK_SIZE_X);

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
					Vector3 worldBlockPos = LocalPositionToGlobalPosition({ x, y, z });
					BlockRenderVO* renderVO = new BlockRenderVO();
					renderVO->pFaceVO = pFaceVO;
					renderVO->pBlockPosition = new Vector3(worldBlockPos.GetX(), worldBlockPos.GetY(), worldBlockPos.GetZ());
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

uint32_t CChunk::GetDisplayListSize() const
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

const Vector3& CChunk::GetCenterPosition() const
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

void CChunk::RemoveBlockByWorldPosition(const Vector3& blockPosition)
{
	Vec3i vec = GetLocalBlockPositionByWorldPosition(blockPosition);

	m_pBlocks[vec.m_x][vec.m_y][vec.m_z] = BlockType::AIR;
	m_IsDirty = true;
}

void CChunk::AddBlockByWorldPosition(const Vector3& blockPosition, BlockType type)
{
	Vec3i vec = GetLocalBlockPositionByWorldPosition(blockPosition);

	if ( m_pBlocks[vec.m_x][vec.m_y][vec.m_z] == BlockType::AIR)
	{
		 m_pBlocks[vec.m_x][vec.m_y][vec.m_z] = type;
		 m_IsDirty = true;
	}
}

Vec3i CChunk::GetLocalBlockPositionByWorldPosition(const Vector3& blockWorldPosition) const
{
	Vec3i vec;
	float blockScale = BLOCK_SIZE;

	vec.m_x = (unsigned int) (fmod(blockWorldPosition.GetX(), CHUNK_BLOCK_SIZE_X) / blockScale);
	vec.m_y = (unsigned int) (fmod(blockWorldPosition.GetY(), CHUNK_BLOCK_SIZE_Y) / blockScale);
	vec.m_z = (unsigned int) (fmod(blockWorldPosition.GetZ(), CHUNK_BLOCK_SIZE_Z) / blockScale);

	return vec;
}

Vector3 CChunk::GetBlockPositionByWorldPosition(const Vector3& worldPosition) const
{
	Vec3i vec = GetLocalBlockPositionByWorldPosition(worldPosition);
	return LocalPositionToGlobalPosition(vec);
}

BlockType CChunk::GetBlockTypeByWorldPosition(const Vector3& worldPosition) const
{
	Vec3i vec = GetLocalBlockPositionByWorldPosition(worldPosition);
	return m_pBlocks[vec.m_x][vec.m_y][vec.m_z];
}

Vector3 CChunk::ValidatePhysicalPosition(const Vector3& position) const
{
	Vector3 pos = GetBlockPositionByWorldPosition(position);
	float currentPos = CHUNK_BLOCK_SIZE_Y - (BLOCK_SIZE);
	bool bValidated = false;
	do
	{
		pos.SetY(currentPos);
		bValidated = (GetBlockTypeByWorldPosition(pos) != BlockType::AIR) || (currentPos == 0);
		currentPos -= BLOCK_SIZE;

	} while(!bValidated);

	return pos;
}

Vector3 CChunk::LocalPositionToGlobalPosition(const Vec3i& localPosition) const
{
	return Vector3( (m_pCenterPosition->GetX() - (CHUNK_BLOCK_SIZE_X / 2) + (localPosition.m_x * BLOCK_SIZE)),
			(m_pCenterPosition->GetY() - (CHUNK_BLOCK_SIZE_Y / 2) + (localPosition.m_y * BLOCK_SIZE)),
			(m_pCenterPosition->GetZ() - (CHUNK_BLOCK_SIZE_Z / 2) + (localPosition.m_z * BLOCK_SIZE)));
}

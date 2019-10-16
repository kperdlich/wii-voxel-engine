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


#include <sstream>
#include "Chunk.h"
#include "world/PerlinNoise.h"
#include "utils/MathHelper.h"
#include "renderer/MasterRenderer.h"
#include "renderer/BlockRenderer.h"
#include "utils/Debug.h"
#include "utils/lockguard.h"
#include "utils/clock.h"

Chunk::Chunk(class GameWorld& gameWorld)
{
	m_pWorldManager = &gameWorld;
}

Chunk::~Chunk()
{
	Clear();

	for (int x = 0; x < CHUNK_SIZE_X; ++x)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; ++y)
		{
			delete[] m_blocks[x][y];
		}

		delete[] m_blocks[x];
	}
	delete[] m_blocks;
}

void Chunk::Init()
{
	m_blocks = new BlockType * *[CHUNK_SIZE_X];
	for (uint32_t x = 0; x < CHUNK_SIZE_X; x++)
	{
		m_blocks[x] = new BlockType * [CHUNK_SIZE_Y];

		for (uint32_t y = 0; y < CHUNK_SIZE_Y; y++)
		{
			m_blocks[x][y] = new BlockType[CHUNK_SIZE_Z];
		}
	}
}

void Chunk::Clear()
{
	DeleteDisplayList();
	ClearBlockRenderList();
}

void Chunk::SetChunkNeighbors()
{
	Vec2i leftChunkPos(m_Position.X - 1, m_Position.Y);
	Vec2i rightChunkPos(m_Position.X + 1, m_Position.Y);
	Vec2i frontChunkPos(m_Position.X, m_Position.Y + 1);
	Vec2i backChunkPos(m_Position.X, m_Position.Y - 1);

	m_pChunkLeft = m_pWorldManager->GetCashedChunkAt(leftChunkPos);
	m_pChunkRight = m_pWorldManager->GetCashedChunkAt(rightChunkPos);
	m_pChunkFront = m_pWorldManager->GetCashedChunkAt(frontChunkPos);
	m_pChunkBack = m_pWorldManager->GetCashedChunkAt(backChunkPos);
}

bool Chunk::NeighborsLoaded()
{
	if (m_pChunkLeft && m_pChunkLeft->IsLoaded())
		return true;

	if (m_pChunkRight && m_pChunkRight->IsLoaded())
		return true;

	if (m_pChunkFront && m_pChunkFront->IsLoaded())
		return true;

	if (m_pChunkBack && m_pChunkBack->IsLoaded())
		return true;

	return false;
}

void Chunk::Render()
{
	m_displayList.Render();
}

void Chunk::SetToAir()
{
	for (uint32_t x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (uint32_t z = 0; z < CHUNK_SIZE_Z; z++)
		{
			for (uint32_t y = 0; y < CHUNK_SIZE_Y; y++)
			{
				m_blocks[x][y][z] = BlockType::AIR;
			}
		}
	}
}

void Chunk::AddBlockToRenderList(BlockType type, const BlockRenderVO& blockRenderVO)
{
	auto blockRenderListIt = m_mBlockRenderList.find(type);
	if (blockRenderListIt != m_mBlockRenderList.end())
	{
		blockRenderListIt->second.emplace_back(blockRenderVO);
	}
	else
	{
		std::vector<BlockRenderVO> blockList;
		blockList.emplace_back(blockRenderVO);
		m_mBlockRenderList.insert(std::pair<BlockType, std::vector<BlockRenderVO> >(type, blockList));
	}
}

bool Chunk::IsBlockVisible(uint32_t iX, uint32_t iY, uint32_t iZ, BlockRenderVO& blockRenderVO)
{
	bool bIsAir = m_blocks[iX][iY][iZ] == BlockType::AIR;

	if (bIsAir)
		return false;

	BlockType top = iY == CHUNK_SIZE_Y - 1 ? BlockType::AIR : m_blocks[iX][iY + 1][iZ];
	BlockType bottom = iY == 0 ? BlockType::AIR : m_blocks[iX][iY - 1][iZ];
	BlockType north = iZ == CHUNK_SIZE_Z - 1 ? BlockType::AIR : m_blocks[iX][iY][iZ + 1];
	BlockType south = iZ == 0 ? BlockType::AIR : m_blocks[iX][iY][iZ - 1];
	BlockType east = iX == CHUNK_SIZE_X - 1 ? BlockType::AIR : m_blocks[iX + 1][iY][iZ];
	BlockType west = iX == 0 ? BlockType::AIR : m_blocks[iX - 1][iY][iZ];

	if (top == BlockType::AIR)
	{
		blockRenderVO.FaceMask |= TOP_FACE;
		blockRenderVO.Faces++;
	}

	if (bottom == BlockType::AIR)
	{
		blockRenderVO.FaceMask |= BOTTOM_FACE;
		blockRenderVO.Faces++;
	}
	if (north == BlockType::AIR)
	{
		blockRenderVO.FaceMask |= FRONT_FACE;
		blockRenderVO.Faces++;
	}
	if (south == BlockType::AIR)
	{
		blockRenderVO.FaceMask |= BACK_FACE;
		blockRenderVO.Faces++;
	}
	if (east == BlockType::AIR)
	{
		blockRenderVO.FaceMask |= RIGHT_FACE;
		blockRenderVO.Faces++;
	}
	if (west == BlockType::AIR)
	{
		blockRenderVO.FaceMask |= LEFT_FACE;
		blockRenderVO.Faces++;
	}

	if (blockRenderVO.Faces > 0)
	{
		blockRenderVO.BlockPosition = LocalPositionToGlobalPosition(Vec3i{ iX, iY, iZ });
		return true;
	}

	return false;
}

void Chunk::BuildBlockRenderList()
{
	m_amountOfBlocks = 0;
	m_amountOfFaces = 0;

	for (uint32_t x = 0; x < CHUNK_SIZE_X; x++)
	{
		for (uint32_t y = 0; y < CHUNK_SIZE_Y; y++)
		{
			for (uint32_t z = 0; z < CHUNK_SIZE_Z; z++)
			{
				BlockRenderVO renderVO;
				if (IsBlockVisible(x, y, z, renderVO))
				{
					AddBlockToRenderList(m_blocks[x][y][z], renderVO);
					m_amountOfBlocks++;
					m_amountOfFaces += renderVO.Faces;
				}
			}
		}
	}
}

void Chunk::ClearBlockRenderList()
{
	m_mBlockRenderList.clear();
}

void Chunk::CreateDisplayList(size_t sizeOfDisplayList)
{
	m_displayList.Begin(sizeOfDisplayList);
}

void Chunk::FinishDisplayList()
{
	m_displayList.End();
    m_bIsDirty = false;
}

uint32_t Chunk::GetDisplayListSize() const
{
	return m_displayList.GetDisplayListSize();
}

uint64_t Chunk::GetAmountOfBlocks() const
{
	return m_amountOfBlocks;
}

uint64_t Chunk::GetAmountOfFaces() const
{
	return m_amountOfFaces;
}

const Vec2i& Chunk::GetPosition() const
{
	return m_Position;
}

void Chunk::DeleteDisplayList()
{
	m_displayList.Clear();
}

void Chunk::RebuildDisplayList()
{
	Clock clock;
	clock.Start();
	BlockRenderer blockRenderer;

	ClearBlockRenderList();
	BuildBlockRenderList();

	DeleteDisplayList();
	CreateDisplayList(MasterRenderer::GetDisplayListSizeForFaces(m_amountOfFaces));

	for (auto it = m_mBlockRenderList.begin(); it != m_mBlockRenderList.end(); ++it)
	{
		Block* pBlockToRender = m_pWorldManager->GetBlockManager().GetBlockByType(it->first);
		blockRenderer.Prepare(&it->second, *pBlockToRender);
		blockRenderer.Draw();
	}

	blockRenderer.Finish();

	FinishDisplayList();
	ClearBlockRenderList();

	m_bNeighbourUpdate = false;
	clock.Stop();
	//LOG("Rebuilding DisplayList took %f s for chunk %f %f", clock.GetSecs(), m_Position.X, m_Position.Y);
}

void Chunk::RemoveBlockByWorldPosition(const Vector3& blockPosition)
{
	Vec3i vec = GetLocalBlockPositionByWorldPosition(blockPosition);

	if (m_blocks[vec.X][vec.Y][vec.Z] != BlockType::AIR)
	{
		m_blocks[vec.X][vec.Y][vec.Z] = BlockType::AIR;
		BlockListUpdated(BlockChangeData{ GetFilePath(m_Position), BlockType::AIR, vec, m_Position });
	}
}

void Chunk::AddBlockByWorldPosition(const Vector3& blockPosition, BlockType type)
{
	Vec3i vec = GetLocalBlockPositionByWorldPosition(blockPosition);

	if (m_blocks[vec.X][vec.Y][vec.Z] == BlockType::AIR)
	{
		m_blocks[vec.X][vec.Y][vec.Z] = type;
		BlockListUpdated(BlockChangeData{ GetFilePath(m_Position), type, vec, m_Position });
	}
}

void Chunk::BlockListUpdated(const BlockChangeData& data)
{
	m_bIsDirty = true;
}

void Chunk::SetPosition(const Vec2i& position)
{
	m_Position = position;
}

void Chunk::SetLoaded(bool value)
{
	lock_guard guard(m_mutex);
	m_bLoadingDone = value;
}

bool Chunk::IsLoaded()
{
	lock_guard guard(m_mutex);
	bool bLoaded = m_bLoadingDone;
	return bLoaded;
}

bool Chunk::HasDisplayList() const
{
	return !m_displayList.IsEmpty();
}

Vec3i Chunk::GetLocalBlockPositionByWorldPosition(const Vector3& blockWorldPosition) const
{
	Vec3i vec;
	float blockScale = BLOCK_SIZE;

	vec.X = (uint32_t)(MathHelper::Mod(blockWorldPosition.GetX(), CHUNK_BLOCK_SIZE_X) / blockScale);
	vec.Y = (uint32_t)(MathHelper::Mod(blockWorldPosition.GetY(), CHUNK_BLOCK_SIZE_Y) / blockScale);
	vec.Z = (uint32_t)(MathHelper::Mod(blockWorldPosition.GetZ(), CHUNK_BLOCK_SIZE_Z) / blockScale);

	return vec;
}

Vector3 Chunk::GetBlockPositionByWorldPosition(const Vector3& worldPosition) const
{
	Vec3i vec = GetLocalBlockPositionByWorldPosition(worldPosition);
	return LocalPositionToGlobalPosition(vec);
}

BlockType Chunk::GetBlockTypeByWorldPosition(const Vector3& worldPosition) const
{
	Vec3i vec = GetLocalBlockPositionByWorldPosition(worldPosition);
	return m_blocks[vec.X][vec.Y][vec.Z];
}


std::string Chunk::GetFilePath(const Vec2i& position)
{
	std::ostringstream filename;
	filename << WORLD_PATH "/";
	filename << position.X;
	filename << '_';
	filename << position.Y;
	filename << ".dat";
	return filename.str();
}

Vector3 Chunk::LocalPositionToGlobalPosition(const Vec3i& localPosition) const
{
	Vector3 vec((double)(CHUNK_GLOBAL_X(m_Position.X) + (localPosition.X * BLOCK_SIZE)),
		(double)(localPosition.Y * BLOCK_SIZE),
		(double)(CHUNK_GLOBAL_Z(m_Position.Y) + (localPosition.Z * BLOCK_SIZE)));

	return vec;
}

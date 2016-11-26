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

#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <stdint.h>
#include "../GameWorld.h"
#include "../../renderer/BlockRenderHelper.h"
#include "../../utils/Vector3.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16

#define CHUNK_BLOCK_SIZE_X (BLOCK_SIZE * CHUNK_SIZE_X)
#define CHUNK_BLOCK_SIZE_Y (BLOCK_SIZE * CHUNK_SIZE_Y)
#define CHUNK_BLOCK_SIZE_Z (BLOCK_SIZE * CHUNK_SIZE_Z)

struct Vec3i {
	unsigned int m_x, m_y, m_z;
};

class CChunk {
public:

	CChunk(class CGameWorld &gameWorld);
	virtual ~CChunk();

	void Init(Vector3& position);
	void RebuildDisplayList();
	void Render();

	bool IsDirty();
	void SetDirty(bool dirty);

	uint32_t GetDisplayListSize() const;
	uint64_t GetAmountOfBlocks() const;
	uint64_t GetAmountOfFaces() const;

	void DeleteDisplayList();

	const Vector3& GetCenterPosition() const;

	void UpdateChunkNeighbors();
	void RemoveBlockByWorldPosition(const Vector3& blockPosition);
	void AddBlockByWorldPosition(const Vector3& blockPosition, BlockType type);
	Vector3 GetBlockPositionByWorldPosition(const Vector3& worldPosition) const;
	BlockType GetBlockTypeByWorldPosition(const Vector3& worldPosition) const;
	Vector3 ValidatePhysicalPosition(const Vector3& position) const;

private:
	void CreateDisplayList(size_t sizeOfDisplayList);
	void FinishDisplayList();
	bool AddBlockToRenderList(BlockType type, const BlockRenderVO& blockRenderVO);
	void RemoveBlock(const Vector3& position);
	void ClearBlockRenderList();
	void BuildBlockRenderList();
	bool IsBlockVisible(uint32_t iX, uint32_t iY, uint32_t iZ, BlockFaceVisibiltyVO* &pFaceVO );
	Vec3i GetLocalBlockPositionByWorldPosition(const Vector3& blockWorldPosition) const;

	Vector3 LocalPositionToGlobalPosition(const Vec3i& localPosition) const;

private:
	bool m_IsDirty;
	bool m_bNeighbourUpdate = false;
	uint32_t m_DisplayListSize = 0;
	void* m_DispList = NULL;

	uint64_t m_AmountOfBlocks = 0;
	uint64_t m_AmountOfFaces = 0;

	Vector3* m_pCenterPosition;

	BlockType*** m_pBlocks;
	std::map<BlockType, std::vector<const BlockRenderVO*> > m_mBlockRenderList;
	class CGameWorld* m_pWorldManager;

	CChunk* m_pChunkLeft = NULL;
	CChunk* m_pChunkRight = NULL;
	CChunk* m_pChunkFront = NULL;
	CChunk* m_pChunkBack = NULL;
};



#endif /* _CHUNK_H_ */

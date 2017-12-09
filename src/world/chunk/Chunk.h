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
#include <string>
#include "chunkdata.h"
#include "../GameWorld.h"
#include "../../renderer/BlockRenderHelper.h"
#include "../../utils/Vector3.h"


class Chunk {
public:

    Chunk(class GameWorld &gameWorld);
    virtual ~Chunk();

    void Init();
    void Build();
    void Clear();
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
    Vector3 GetPhysicalPosition(const Vector3& position) const;

    BlockType*** GetBlocks() const
    {
        return m_blocks;
    }


    void SetCenterPosition(const Vector3 &centerPosition);

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

    void CreateTrees();
    void BlockListUpdated(const BlockChangeData &data);

private:    
    bool m_bIsDirty             = false;
    bool m_bNeighbourUpdate     = false;
    uint32_t m_displayListSize  = 0;
    void* m_pDispList           = nullptr;

    uint32_t m_amountOfBlocks   = 0;
    uint32_t m_amountOfFaces    = 0;

    Vector3 m_centerPosition;

    BlockType*** m_blocks;
	std::map<BlockType, std::vector<const BlockRenderVO*> > m_mBlockRenderList;
	class GameWorld* m_pWorldManager;

    Chunk* m_pChunkLeft         = nullptr;
    Chunk* m_pChunkRight        = nullptr;
    Chunk* m_pChunkFront        = nullptr;
    Chunk* m_pChunkBack         = nullptr;
};



#endif /* _CHUNK_H_ */

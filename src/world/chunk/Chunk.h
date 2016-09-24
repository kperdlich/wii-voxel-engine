/*
 * Chunk.h
 *
 *  Created on: 13.07.2016
 *      Author: Kevin
 */

#ifndef _CHUNK_H_
#define _CHUNK_H_

#include <stdint.h>
#include "../GameWorld.h"
#include "../../renderer/BlockRenderHelper.h"
#include "../../utils/Vector3f.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16


class CChunk {
public:

	CChunk(class CGameWorld &gameWorld);
	virtual ~CChunk();

	void Init(Vector3f& position);
	void RebuildDisplayList();
	void Render();

	bool IsDirty();
	void SetDirty(bool dirty);

	uint32_t GetDisplayListSize() const;
	uint64_t GetAmountOfBlocks() const;
	uint64_t GetAmountOfFaces() const;

	void DeleteDisplayList();

	const Vector3f& GetCenterPosition() const;

	void UpdateChunkNeighbors();
	void RemoveBlockByWorldPosition(const Vector3f& blockPosition);
	void AddBlockByWorldPosition(const Vector3f& blockPosition, BlockType type);
	Vector3f GetBlockPositionByWorldPosition(const Vector3f& worldPosition) const;
	BlockType GetBlockTypeByWorldPosition(const Vector3f& worldPosition) const;
	Vector3f ValidatePhysicalPosition(const Vector3f& position) const;

private:
	void CreateDisplayList(size_t sizeOfDisplayList);
	void FinishDisplayList();
	bool AddBlockToRenderList(BlockType type, const BlockRenderVO& blockRenderVO);
	void RemoveBlock(const Vector3f& position);
	void ClearBlockRenderList();
	void BuildBlockRenderList();
	bool IsBlockVisible(uint32_t iX, uint32_t iY, uint32_t iZ, BlockFaceVisibiltyVO* &pFaceVO );
	void GetLocalBlockPositionByWorldPosition(const Vector3f& blockWorldPosition, unsigned int* x, unsigned int* y, unsigned int* z) const;

private:
	bool m_IsDirty;
	bool m_bNeighbourUpdate = false;
	uint32_t m_DisplayListSize = 0;
	void* m_DispList = NULL;

	uint64_t m_AmountOfBlocks = 0;
	uint64_t m_AmountOfFaces = 0;

	Vector3f* m_pCenterPosition;

	BlockType*** m_pBlocks;
	std::map<BlockType, std::vector<const BlockRenderVO*> > m_mBlockRenderList;
	class CGameWorld* m_pWorldManager;

	CChunk* m_pChunkLeft = NULL;
	CChunk* m_pChunkRight = NULL;
	CChunk* m_pChunkFront = NULL;
	CChunk* m_pChunkBack = NULL;
};

#endif /* _CHUNK_H_ */

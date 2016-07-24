/*
 * Chunk.h
 *
 *  Created on: 13.07.2016
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_CHUNK_CHUNK_H_
#define SRC_GUI_WORLD_CHUNK_CHUNK_H_

#include <stdint.h>
#include "../GameWorld.h"
#include "../blocks/BlockRenderHelper.h"
#include "../../../utils/Vector3f.h"

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

	uint32_t GetDisplayListSize();
	uint64_t GetAmountOfBlocks();
	uint64_t GetAmountOfFaces();

	void DeleteDisplayList();

	Vector3f& GetCenterPosition();

	void UpdateChunkNeighbors();
	void RemoveBlockByWorldPosition(Vector3f blockPosition);
	Vector3f GetBlockPositionByWorldPosition(Vector3f& worldPosition);

private:
	void CreateDisplayList(size_t sizeOfDisplayList);
	void FinishDisplayList();
	bool AddBlockToRenderList(BlockType type, BlockRenderData& blockRenderData);
	void RemoveBlock(Vector3f& position);
	void ClearBlockRenderList();
	void BuildBlockRenderList();
	bool IsBlockVisible(uint32_t iX, uint32_t iY, uint32_t iZ, BlockFaceVisibiltyData* &pFaceData );
	void GetLocalBlockPositionByWorldPosition(Vector3f& blockWorldPosition, unsigned int* x, unsigned int* y, unsigned int* z);

private:
	bool m_IsDirty;
	bool m_bNeighbourUpdate = false;
	uint32_t m_DisplayListSize = 0;
	void* m_DispList = NULL;

	uint64_t m_AmountOfBlocks = 0;
	uint64_t m_AmountOfFaces = 0;

	Vector3f* m_pCenterPosition;

	BlockType*** m_pBlocks;
	std::map<BlockType, std::vector<BlockRenderData*> > m_mBlockRenderList;
	class CGameWorld* m_pWorldManager;

	CChunk* m_pChunkLeft = NULL;
	CChunk* m_pChunkRight = NULL;
	CChunk* m_pChunkFront = NULL;
	CChunk* m_pChunkBack = NULL;
};

#endif /* SRC_GUI_WORLD_CHUNK_CHUNK_H_ */

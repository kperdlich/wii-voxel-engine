/*
 * BlockManager.h
 *
 *  Created on: 23.01.2016
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_BLOCKMANAGER_H_
#define SRC_GUI_WORLD_BLOCKMANAGER_H_


#include "Block.h"
#include "BlockRenderer.h"
#include "../../../handler/TextureHandler.h"
#include "../../../utils/Vector3f.h"
#include <map>
#include <vector>

#define BLOCK_SIZE .5f

#define BLOCK_TYPE_DIRT 0
#define BLOCK_TYPE_GRASS 1

#define BLOCK_TEXTURE_DIRT "BLOCK_TEXTURE_DIRT"
#define BLOCK_TEXTURE_GRASS "BLOCK_TEXTURE_GRASS"


class CBlockManager {
public:
	CBlockManager( TextureHandler* ptextureHandler );
	virtual ~CBlockManager();
	void LoadBlocks();
	void UnloadBlocks();
	void RenderBlockList();
	bool AddBlockToRenderList(unsigned int iBlockType, Vector3f *position);
	void ClearBlockRenderList();

private:
	CBlock* GetBlockByType(unsigned int type);

	std::map<unsigned int, CBlock*> m_blocks;
	std::map<unsigned int, std::vector<Vector3f*> > m_mBlockRenderList;
	TextureHandler* m_pTextureHandler;
	BlockRenderer* m_blockRenderer;

};

#endif /* SRC_GUI_WORLD_BLOCKMANAGER_H_ */

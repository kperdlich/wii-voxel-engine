/*
 * BlockManager.h
 *
 *  Created on: 23.01.2016
 *      Author: Kevin
 */

#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

#include <map>
#include <vector>
#include "Block.h"
#include "../../renderer/BlockRenderer.h"
#include "../../textures/TextureHandler.h"
#include "../../utils/Vector3f.h"

#define BLOCK_SIZE .5f

#define BLOCK_TEXTURE_DIRT "BLOCK_TEXTURE_DIRT"
#define BLOCK_TEXTURE_GRASS "BLOCK_TEXTURE_GRASS"

enum BlockType {

	AIR,
	DIRT,
	GRASS
};

class CBlockManager {
public:
	CBlockManager( TextureHandler& ptextureHandler );
	virtual ~CBlockManager();
	void LoadBlocks();
	void UnloadBlocks();

	CBlock* GetBlockByType(const BlockType type);

private:

	std::map<BlockType, CBlock*> m_blocks;
	std::map<BlockType, std::vector<Vector3f*> > m_mBlockRenderList;
	TextureHandler* m_pTextureHandler;
	BlockRenderer* m_blockRenderer;

};

#endif /* _BLOCKMANAGER_H_ */

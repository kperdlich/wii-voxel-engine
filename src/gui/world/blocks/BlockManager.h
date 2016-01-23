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
	void Render(Vector3f position, unsigned int blockType);

private:
	CBlock* GetBlockByType(unsigned int type);

	std::map<int, CBlock*> m_blocks;
	TextureHandler* m_pTextureHandler;
	BlockRenderer* m_blockRenderer;

};

#endif /* SRC_GUI_WORLD_BLOCKMANAGER_H_ */

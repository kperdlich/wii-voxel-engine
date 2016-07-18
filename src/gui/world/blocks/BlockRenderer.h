/*
 * BlockRenderer.h
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_RENDERER_BLOCKRENDERER_H_
#define SRC_ENTITY_RENDERER_BLOCKRENDERER_H_

#include "BlockRenderHelper.h"
#include "../../../gui/Texture.h"
#include <vector>

class BlockRenderer {
public:
	BlockRenderer();
	virtual ~BlockRenderer();
	void Prepare(std::vector<BlockRenderData*> *positionList, float blockSize, Texture* ptexture);
	void Rebuild();
	void Finish();

private:
	float m_renderBlockSize;
	std::vector<BlockRenderData*>* m_positions;


};

#endif /* SRC_ENTITY_RENDERER_BLOCKRENDERER_H_ */

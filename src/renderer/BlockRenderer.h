/*
 * BlockRenderer.h
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#ifndef _BLOCKRENDERER_H_
#define _BLOCKRENDERER_H_

#include "BlockRenderHelper.h"
#include "../textures/Texture.h"
#include <vector>

class BlockRenderer {
public:
	BlockRenderer();
	virtual ~BlockRenderer();
	void Prepare(std::vector<const BlockRenderVO*> *positionList, float blockSize, const Texture* ptexture);
	void Rebuild();
	void Finish();
	void DrawFocusOnSelectedCube(const Vector3f& blockWorldPosition);

private:
	float m_renderBlockSize = 0.0f;
	std::vector<const BlockRenderVO*>* m_positions;


};

#endif /* _BLOCKRENDERER_H_ */

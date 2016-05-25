/*
 * BlockRenderer.h
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_RENDERER_BLOCKRENDERER_H_
#define SRC_ENTITY_RENDERER_BLOCKRENDERER_H_

#include "../../../utils/Vector3f.h"
#include "../../../gui/Texture.h"
#include <vector>

class BlockRenderer {
public:
	BlockRenderer();
	virtual ~BlockRenderer();
	void Prepare(std::vector<Vector3f*> *positionList, float blockSize, Texture* ptexture);
	void render(/*Vector3f position, float blockSize*/);
	void Finish();

private:
	float m_renderBlockSize;
	std::vector<Vector3f*>* m_positions;
};

#endif /* SRC_ENTITY_RENDERER_BLOCKRENDERER_H_ */

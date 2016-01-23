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

class BlockRenderer {
public:
	BlockRenderer();
	virtual ~BlockRenderer();
	void render(Vector3f position, float blockSize, Texture* ptexture);
};

#endif /* SRC_ENTITY_RENDERER_BLOCKRENDERER_H_ */

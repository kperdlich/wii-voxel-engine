/*
 * BlockRenderer.h
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_RENDERER_BLOCKRENDERER_H_
#define SRC_ENTITY_RENDERER_BLOCKRENDERER_H_

#include "EntityRenderer.h"

class BlockRenderer: public EntityRenderer {
public:
	BlockRenderer(Entity* entity);
	virtual ~BlockRenderer();
	void render();
};

#endif /* SRC_ENTITY_RENDERER_BLOCKRENDERER_H_ */

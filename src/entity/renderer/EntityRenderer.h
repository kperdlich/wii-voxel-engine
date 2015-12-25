/*
 * EntityRenderer.h
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#ifndef SRC_ENTITY_RENDERER_ENTITYRENDERER_H_
#define SRC_ENTITY_RENDERER_ENTITYRENDERER_H_

#include "../Entity.h"
#include "../../gui/Texture.h"
#include "../../handler/TextureHandler.h"

class Entity;

class EntityRenderer {
public:
	EntityRenderer(Entity* entity);
	virtual ~EntityRenderer();
	virtual void render();
	void setTexture( Texture* texture );
	Texture* getTexture();
protected:
	TextureHandler* getTextureHandler();
	Texture* m_entityTexture;
	Entity* m_Entity;
};

#endif /* SRC_ENTITY_RENDERER_ENTITYRENDERER_H_ */

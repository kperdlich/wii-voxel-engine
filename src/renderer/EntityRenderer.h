/*
 * EntityRenderer.h
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#ifndef _ENTITYRENDERER_H_
#define _ENTITYRENDERER_H_

#include "../entity/Entity.h"
#include "../textures/TextureHandler.h"
#include "../textures/Texture.h"

class Entity;

class EntityRenderer {
public:
	EntityRenderer(Entity* entity);
	virtual ~EntityRenderer();
	virtual void Render() const;
	void SetTexture( Texture* texture );
	Texture* GetTexture() const;
protected:
	TextureHandler& GetTextureHandler();
	Texture* m_entityTexture;
	Entity* m_Entity;
};

#endif /* _ENTITYRENDERER_H_ */

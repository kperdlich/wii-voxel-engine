/*
 * Renderer3D.h
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#ifndef _RENDERER3D_H_
#define _RENDERER3D_H_

#include "Renderer.h"
#include "../textures/BasicTexture.h"
#include "../entity/Entity.h"

class Renderer3D: public Renderer {
public:
	Renderer3D();
	virtual ~Renderer3D();
	void draw2DTexture( BasicTexture* tex );
	void drawEntity(const class Entity* entity) const;
};

#endif /* _RENDERER3D_H_ */

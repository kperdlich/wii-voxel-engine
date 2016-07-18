/*
 * Renderer3D.h
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_RENDERER_RENDERER3D_H_
#define SRC_GUI_RENDERER_RENDERER3D_H_

#include "Renderer.h"
#include "../BasicTexture.h"
#include "../../entity/Entity.h"

class Renderer3D: public Renderer {
public:
	Renderer3D();
	virtual ~Renderer3D();
	void draw2DTexture( BasicTexture* tex );
	void drawEntity(class Entity* entity);
};

#endif /* SRC_GUI_RENDERER_RENDERER3D_H_ */

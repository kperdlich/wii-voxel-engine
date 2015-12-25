/*
 * Renderer3D.cpp
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#include <grrlib.h>
#include "Renderer3D.h"
#include "../Texture.h"

Renderer3D::Renderer3D() {
	// TODO Auto-generated constructor stub

}

Renderer3D::~Renderer3D() {
	// TODO Auto-generated destructor stub
}

void Renderer3D::draw2DTexture( BasicTexture* tex ) {
	Texture* tx = (Texture*) tex;
	GRRLIB_DrawImg( tx->getX(), tx->getY(), tx->getNativeTexture(), 0, 1, 1, tx->getColor() );
}

void Renderer3D::drawEntity(Entity* entity) {
	entity->getRenderer()->render();
}

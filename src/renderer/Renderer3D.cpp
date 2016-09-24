/*
 * Renderer3D.cpp
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#include "Renderer3D.h"
#include "../core/grrlib.h"
#include "../textures/Texture.h"

Renderer3D::Renderer3D() {}

Renderer3D::~Renderer3D() {}

void Renderer3D::draw2DTexture( BasicTexture* tex )
{
	Texture* tx = (Texture*) tex;
	GRRLIB_DrawImg( tx->GetX(), tx->GetY(), tx->GetNativeTexture(), 0, 1, 1, tx->GetColor() );
}

void Renderer3D::drawEntity(const Entity* entity) const
{
	entity->GetRenderer()->Render();
}

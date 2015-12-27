/*
 * Renderer2D.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#include "Renderer2D.h"


void Renderer2D::drawTexture(Texture* texture, const f32 xpos, const f32 ypos,
		const f32 degrees, const f32 scaleX, const f32 scaleY,
		const f32 color)
{
	GRRLIB_DrawImg( xpos , ypos, texture->getNativeTexture(), degrees, scaleX, scaleY, color);
}

void Renderer2D::drawTexture(Texture* texture, const f32 xpos, const f32 ypos) {
	GRRLIB_DrawImg( xpos, ypos, texture->getNativeTexture(), 0, 1, 1, GRRLIB_WHITE );
}

Renderer2D::Renderer2D() {

}

Renderer2D::~Renderer2D() {
}

void Renderer2D::drawTexture(BasicTexture* basicTexture)
{
	switch( basicTexture->getTextureType() )
	{
		case SPRITE:
		{
			Texture* tx = (Texture*) basicTexture;
			GRRLIB_DrawImg( tx->getX(), tx->getY(), tx->getNativeTexture(), 0, 1, 1, tx->getColor() );
			break;
		}
		case TILE:
		{
			Tile* ti = (Tile*) basicTexture;
			GRRLIB_DrawTile(ti->getX(), ti->getY(), ti->getSpriteSheet()->getNativeTexture(), 0, 1, 1, GRRLIB_WHITE, ti->getSheetIndex());
			break;
		}
		case LABEL:
		{
			LabelTexture* label = (LabelTexture*) basicTexture;
			GRRLIB_PrintfTTF( label->getX(), label->getY(), label->getFont(), label->getText(), label->getFontSize(), label->getTextColor() );
			break;
		}
		default:
			break;
	}
}

void Renderer2D::drawTile(SpriteSheet* tilemap, const f32 xpos, const f32 ypos,
		const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color,
		const int frame)
{
	GRRLIB_DrawTile(xpos, ypos, tilemap->getNativeTexture(), degrees, scaleX, scaleY, color, frame);
}




/*
 * SpriteSheet.cpp
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#include "SpriteSheet.h"
#include "../utils/TileHelper.h"

SpriteSheet::SpriteSheet( const unsigned char* texture, const u16 id ) : Texture( 0, 0, texture, id )
{
	m_visible = false;
}

SpriteSheet::~SpriteSheet() {}

void SpriteSheet::LoadTexture()
{
	Texture::LoadTexture();
	GRRLIB_InitTileSet( m_Texture, TILE_WIDTH, TILE_HEIGHT, 0 );
}

void SpriteSheet::UnloadTexture() {}

txTypes SpriteSheet::GetTextureType() const
{
	return SPRITE_SHEET;
}

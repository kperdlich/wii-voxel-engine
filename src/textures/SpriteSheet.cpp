/***
 *
 * Copyright (C) 2016 DaeFennek
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
***/

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
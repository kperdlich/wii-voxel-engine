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

#include "Tile.h"
#include "../utils/TileHelper.h"

Tile::Tile( float x, float y, uint32_t index, class SpriteSheet* tileSheet, const uint16_t id ) :
	m_sheetIndex( index ), m_TileSheet(tileSheet), BasicTexture(x, y, id)
{
	m_bVisible = true;

}

Tile::~Tile() {
}

ETextureType Tile::GetTextureType() const
{
	return TILE;
}

bool Tile::IsVisible() const
{
	return m_TileSheet->IsLoaded() && m_bVisible;
}

SpriteSheet* Tile::GetSpriteSheet() {
	return m_TileSheet;
}

uint32_t Tile::GetSheetIndex()
{
	return m_sheetIndex;
}

uint32_t Tile::GetWidth() const
{
	return TILE_WIDTH;
}

uint32_t Tile::GetHeight() const
{
	return TILE_HEIGHT;
}

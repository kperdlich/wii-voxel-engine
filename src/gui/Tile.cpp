/*
 * Tile.cpp
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#include "Tile.h"
#include "../utils/TileHelper.h"

Tile::Tile( float x, float y, int index, SpriteSheet* tileSheet, const u16 id ) :
	m_sheetIndex( index ), m_TileSheet(tileSheet), BasicTexture(x, y, id)
{
	m_visible = true;

}

Tile::~Tile() {
}

txTypes Tile::getTextureType() {
	return TILE;
}

bool Tile::isVisible() {
	return m_TileSheet->isLoaded() && m_visible;
}

SpriteSheet* Tile::getSpriteSheet() {
	return m_TileSheet;
}

int Tile::getSheetIndex() {
	return m_sheetIndex;
}

uint Tile::getWidth() {
	return TILE_WIDTH;
}

uint Tile::getHeight() {
	return TILE_HEIGHT;
}

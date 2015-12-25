/*
 * Tile.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_TILE_H_
#define SRC_GUI_TILE_H_

#include "SpriteSheet.h"
#include "BasicTexture.h"

class SpriteSheet;

class Tile : public BasicTexture {
public:
	Tile(float x, float y, int index, SpriteSheet* tileSheet, const u16 id  );
	virtual ~Tile();
	txTypes getTextureType();

	bool isVisible();
	SpriteSheet* getSpriteSheet();
	int getSheetIndex();

	uint getWidth();
	uint getHeight();

private:
	int m_sheetIndex;
	SpriteSheet* m_TileSheet;

};

#endif /* SRC_GUI_TILE_H_ */

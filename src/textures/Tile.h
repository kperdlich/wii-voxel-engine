/*
 * Tile.h
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#ifndef _TILE_H_
#define _TILE_H_

#include "SpriteSheet.h"
#include "BasicTexture.h"


class Tile : public BasicTexture {
public:
	Tile(float x, float y, int index, class SpriteSheet* tileSheet, const u16 id  );
	virtual ~Tile();
	virtual txTypes GetTextureType() const override;

	virtual bool IsVisible() const override;
	SpriteSheet* getSpriteSheet();
	int getSheetIndex();

	virtual uint GetWidth() const override;
	virtual uint GetHeight() const override;

private:
	int m_sheetIndex;
	SpriteSheet* m_TileSheet;

};

#endif /* _TILE_H_ */

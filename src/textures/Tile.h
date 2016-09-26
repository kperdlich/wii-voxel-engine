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

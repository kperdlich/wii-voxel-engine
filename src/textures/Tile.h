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
    Tile(float x, float y, uint32_t index, class SpriteSheet* tileSheet, const uint16_t id  );
	virtual ~Tile();
	virtual ETextureType GetTextureType() const override;

	virtual bool IsVisible() const override;
    SpriteSheet* GetSpriteSheet();
    uint32_t GetSheetIndex();

    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;

private:
    uint32_t m_sheetIndex;
	SpriteSheet* m_TileSheet;

};

#endif /* _TILE_H_ */

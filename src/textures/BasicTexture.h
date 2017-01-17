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

#ifndef _BASICTEXTURE_H_
#define _BASICTEXTURE_H_

#include "../core/grrlib.h"

enum ETextureType {
	INVALID,
	SPRITE,
	SPRITE_SHEET,
	TILE,
	LABEL
};

class BasicTexture {
public:
    BasicTexture(float x, float y, uint16_t id);
	virtual ~BasicTexture();
    virtual ETextureType GetTextureType() const;

	virtual void LoadTexture();
	virtual void UnloadTexture();

	float GetX() const;
	void SetX(float x);
	float GetY() const;
	void SetY(float y);

    void SetColor(uint32_t color);
    uint32_t GetColor() const;

    virtual uint32_t GetWidth() const;
    virtual uint32_t GetHeight() const;

    uint16_t GetId() const;

	virtual bool IsVisible() const;
	virtual void SetVisible(bool value);

protected:
	float m_x, m_y;
    const uint16_t m_id;
	bool m_bVisible;
    uint32_t m_color;
};

#endif /* _BASICTEXTURE_H_ */

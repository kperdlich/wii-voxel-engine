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

#ifndef _LABELTEXTURE_H_
#define _LABELTEXTURE_H_

#include "../core/grrlib.h"
#include "BasicTexture.h"

class LabelTexture: public BasicTexture {
public:
    LabelTexture( const char* text, float x, float y, const uint16_t id, GRRLIB_ttfFont* font, uint32_t fontSize, uint32_t color );
	virtual ~LabelTexture();
	virtual ETextureType GetTextureType() const override;

	GRRLIB_ttfFont& getFont() const;
	const char* getText() const;
    uint32_t getFontSize() const;
    uint32_t getTextColor() const;

	virtual bool IsVisible() const override;

    void setFontSize(uint32_t fontSize);
    void setTextColor(uint32_t textColor);

private:
	const char* m_text;
	GRRLIB_ttfFont* m_font;
    uint32_t m_fontSize = 0;
    uint32_t m_textColor = 0;
};

#endif /* _LABELTEXTURE_H_ */

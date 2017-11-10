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

#ifndef _LABEL_H_
#define _LABEL_H_

#include "../core/grrlib.h"
#include "Sprite.h"

class Label: public Sprite {
public:
    Label( const char* text, float x, float y, TextureLoadingData textureData, GRRLIB_ttfFont* font, uint32_t fontSize, uint32_t color);
    virtual ~Label();
	virtual ETextureType GetTextureType() const override;

    GRRLIB_ttfFont& GetFont() const;
    const char* GetText() const;
    uint32_t GetFontSize() const;
    uint32_t GetTextColor() const;

    virtual bool IsVisible() const override;

    void SetFontSize(uint32_t fontSize);
    void SetTextColor(uint32_t textColor);

private:
	const char* m_text;
	GRRLIB_ttfFont* m_font;
    uint32_t m_fontSize = 0;
    uint32_t m_textColor = 0;
};

#endif /* _LABEL_H_ */

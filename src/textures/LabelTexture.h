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
	LabelTexture( const char* text, float x, float y, const u16 id, GRRLIB_ttfFont* font, uint fontSize, u32 color );
	virtual ~LabelTexture();
	virtual txTypes GetTextureType() const override;

	GRRLIB_ttfFont& getFont() const;
	const char* getText() const;
	uint getFontSize() const;
	u32 getTextColor() const;

	virtual bool IsVisible() const override;

	void setFontSize(uint fontSize);
	void setTextColor(u32 textColor);

private:
	const char* m_text;
	GRRLIB_ttfFont* m_font;
	uint m_fontSize = 0;
	u32 m_textColor = 0;
};

#endif /* _LABELTEXTURE_H_ */

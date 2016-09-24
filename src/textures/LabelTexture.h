/*
 * LabelTexture.h
 *
 *  Created on: 30.06.2015
 *      Author: Kevin
 */

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

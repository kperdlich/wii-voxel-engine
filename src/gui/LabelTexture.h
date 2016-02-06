/*
 * LabelTexture.h
 *
 *  Created on: 30.06.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_LABELTEXTURE_H_
#define SRC_GUI_LABELTEXTURE_H_

#include "../core/grrlib.h"
#include "BasicTexture.h"

class LabelTexture: public BasicTexture {
public:
	LabelTexture( const char* text, float x, float y, const u16 id, GRRLIB_ttfFont* font, uint fontSize, u32 color );
	virtual ~LabelTexture();
	txTypes getTextureType();

	GRRLIB_ttfFont* getFont();
	const char* getText();
	uint getFontSize();
	u32 getTextColor();

	bool isVisible();

	void setFontSize(uint fontSize);
	void setTextColor(u32 textColor);

private:
	const char* m_text;
	GRRLIB_ttfFont* m_font;
	uint m_fontSize;
	u32 m_textColor;
};

#endif /* SRC_GUI_LABELTEXTURE_H_ */

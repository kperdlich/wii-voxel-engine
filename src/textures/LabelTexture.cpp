/*
 * LabelTexture.cpp
 *
 *  Created on: 30.06.2015
 *      Author: Kevin
 */

#include "LabelTexture.h"

LabelTexture::LabelTexture( const char* text, float x, float y, const u16 id, GRRLIB_ttfFont* font, uint fontSize, u32 color ) : m_text( text ), m_font( font ), m_fontSize( fontSize ), m_textColor( color ), BasicTexture(x, y,id ) {

	m_visible = true;

}

LabelTexture::~LabelTexture() {}

GRRLIB_ttfFont& LabelTexture::getFont() const
{
	return *m_font;
}

const char* LabelTexture::getText() const
{
	return m_text;
}

txTypes LabelTexture::GetTextureType() const
{
	return LABEL;
}

uint LabelTexture::getFontSize() const
{
	return m_fontSize;
}

u32 LabelTexture::getTextColor() const
{
	return m_textColor;
}

bool LabelTexture::IsVisible() const
{
	return true;
}

void LabelTexture::setFontSize(uint fontSize)
{
	m_fontSize = fontSize;

}

void LabelTexture::setTextColor(u32 textColor)
{
	m_textColor = textColor;
}

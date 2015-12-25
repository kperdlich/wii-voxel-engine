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

LabelTexture::~LabelTexture() {

}

GRRLIB_ttfFont* LabelTexture::getFont() {
	return m_font;
}

const char* LabelTexture::getText() {
	return m_text;
}

txTypes LabelTexture::getTextureType() {
	return LABEL;
}

uint LabelTexture::getFontSize() {
	return m_fontSize;
}

u32 LabelTexture::getTextColor() {
	return m_textColor;
}

bool LabelTexture::isVisible() {
	return true;
}

void LabelTexture::setFontSize(uint fontSize) {
	m_fontSize = fontSize;

}

void LabelTexture::setTextColor(u32 textColor) {
	m_textColor = textColor;
}

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

#include "LabelSprite.h"

Label::Label( const char* text, float x, float y, TextureLoadingData textureData, const uint16_t id, GRRLIB_ttfFont* font, uint32_t fontSize, uint32_t color )
    : m_text( text ), m_font( font ), m_fontSize( fontSize ), m_textColor( color ), Sprite(x, y, textureData, id ) {}

Label::~Label() {}

GRRLIB_ttfFont& Label::getFont() const
{
	return *m_font;
}

const char* Label::getText() const
{
	return m_text;
}

ETextureType Label::GetTextureType() const
{
	return LABEL;
}

uint32_t Label::getFontSize() const
{
	return m_fontSize;
}

uint32_t Label::getTextColor() const
{
	return m_textColor;
}

bool Label::IsVisible() const
{
	return true;
}

void Label::setFontSize(uint32_t fontSize)
{
	m_fontSize = fontSize;

}

void Label::setTextColor(u32 textColor)
{
	m_textColor = textColor;
}

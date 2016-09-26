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

#include "UITextureElement.h"

UITextureElement::UITextureElement(int x, int y,
		const char* name, BasicTexture* tex) : UIElement( x, y, tex->GetWidth(), tex->GetHeight(), name ), m_texture(tex) {
	m_texture->SetX(x);
	m_texture->SetY(y);

}

UITextureElement::UITextureElement(const char* name, BasicTexture* tex) : UIElement( 0, 0, tex->GetWidth(), tex->GetHeight(), name ), m_texture(tex)
{

}

UITextureElement::~UITextureElement()
{

}

void UITextureElement::Load()

{
}


void UITextureElement::SetX(int x) {
	UIElement::SetX(x);
	m_texture->SetX(x);
}


void UITextureElement::SetY(int y) {
	UIElement::SetY(y);
	m_texture->SetY(y);
}

void UITextureElement::SetColor(u32 color)
{
	m_texture->SetColor(color);
}

u32 UITextureElement::GetColor() const
{
	return m_texture->GetColor();
}

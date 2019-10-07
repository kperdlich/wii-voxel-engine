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

#include "components/UiTextureElement.h"

UiTextureElement::UiTextureElement(uint32_t x, uint32_t y,
        const char* name, Sprite* tex) : UiElement( x, y, tex->GetWidth(), tex->GetHeight(), name ), m_sprite(tex)
{
    m_sprite->SetX(x);
    m_sprite->SetY(y);

}

UiTextureElement::UiTextureElement(const char* name, Sprite* tex) : UiElement( 0, 0, tex->GetWidth(), tex->GetHeight(), name ), m_sprite(tex)
{

}

UiTextureElement::~UiTextureElement()
{
    if (m_sprite)
    {
        delete m_sprite;
    }
}

void UiTextureElement::Load()
{
}


void UiTextureElement::SetX(uint32_t x)
{
	UiElement::SetX(x);
    m_sprite->SetX(x);
}


void UiTextureElement::SetY(uint32_t y)
{
	UiElement::SetY(y);
    m_sprite->SetY(y);
}

void UiTextureElement::SetColor(u32 color)
{
    m_sprite->SetColor(color);
}

u32 UiTextureElement::GetColor() const
{
    return m_sprite->GetColor();
}

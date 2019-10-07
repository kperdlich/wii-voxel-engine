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


#include "components/UiElement.h"

UiElement::UiElement(uint32_t x, uint32_t y, float width, float height, const char* name) :
        m_x( x ), m_y( y ), m_width( width ), m_height( height ), m_pName( name )
{

    this->m_bVisible = true;
}

UiElement::~UiElement()
{
}



float UiElement::GetHeight() const
{
	return m_height;
}

void UiElement::SetHeight(float height)
{
	m_height = height;
}

const char* UiElement::GetName() const
{
    return m_pName;
}

bool UiElement::IsVisible() const
{
    return m_bVisible;
}

void UiElement::SetVisible(bool visible)
{
    m_bVisible = visible;
}

float UiElement::GetWidth() const
{
	return m_width;
}

void UiElement::SetWidth(float width)
{
	m_width = width;
}

uint32_t UiElement::GetX() const
{
	return m_x;
}

void UiElement::SetX(uint32_t x)
{
	m_x = x;
}

uint32_t UiElement::GetY() const
{
	return m_y;
}

void UiElement::SetY(uint32_t y)
{
	m_y = y;
}

void UiElement::Update() {}

void UiElement::Load(){}

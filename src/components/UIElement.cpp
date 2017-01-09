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


#include "UIElement.h"

UIElement::UIElement(uint32_t x, uint32_t y, float width, float height, const char* name) :
		m_x( x ), m_y( y ), m_width( width ), m_height( height ), m_Name( name )
{

	this->m_visible = true;
}

UIElement::~UIElement()
{
}



float UIElement::GetHeight() const
{
	return m_height;
}

void UIElement::SetHeight(float height)
{
	m_height = height;
}

const char* UIElement::GetName() const
{
	return m_Name;
}

bool UIElement::IsVisible() const
{
	return m_visible;
}

void UIElement::SetVisible(bool visible)
{
	m_visible = visible;
}

float UIElement::GetWidth() const
{
	return m_width;
}

void UIElement::SetWidth(float width)
{
	m_width = width;
}

uint32_t UIElement::GetX() const
{
	return m_x;
}

void UIElement::SetX(uint32_t x)
{
	m_x = x;
}

uint32_t UIElement::GetY() const
{
	return m_y;
}

void UIElement::SetY(uint32_t y)
{
	m_y = y;
}

void UIElement::Update() {}

void UIElement::Load(){}

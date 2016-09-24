/*
 * 2DUIElement.cpp
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */


#include "UIElement.h"

UIElement::UIElement(int x, int y, float width, float height, const char* name) :
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

int UIElement::GetX() const
{
	return m_x;
}

void UIElement::SetX(int x)
{
	m_x = x;
}

int UIElement::GetY() const
{
	return m_y;
}

void UIElement::SetY(int y)
{
	m_y = y;
}

void UIElement::Update() {}

void UIElement::Load(){}

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



float UIElement::getHeight()
{
		return m_height;
}

void UIElement::setHeight(float height)
{
	m_height = height;
}

const char* UIElement::getName()
{
	return m_Name;
}

bool UIElement::isVisible()
{
	return m_visible;
}

void UIElement::setVisible(bool visible)
{
	m_visible = visible;
}

float UIElement::getWidth()
{
	return m_width;
}

void UIElement::setWidth(float width)
{
	m_width = width;
}

int UIElement::getX()
{
	return m_x;
}

void UIElement::setX(int x)
{
	m_x = x;
}

int UIElement::getY()
{
	return m_y;
}

void UIElement::setY(int y)
{
	m_y = y;
}

void UIElement::update() {
}

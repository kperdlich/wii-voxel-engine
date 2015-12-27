/*
 * UITextureElement.cpp
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#include "UITextureElement.h"

UITextureElement::UITextureElement(int x, int y,
		const char* name, BasicTexture* tex) : UIElement( x, y, tex->getWidth(), tex->getHeight(), name ), m_texture(tex) {
	m_texture->setX(x);
	m_texture->setY(y);

}

UITextureElement::UITextureElement(const char* name, BasicTexture* tex) : UIElement( 0, 0, tex->getWidth(), tex->getHeight(), name ), m_texture(tex)
{

}

UITextureElement::~UITextureElement()
{
}

void UITextureElement::load()

{
}


void UITextureElement::setX(int x) {
	UIElement::setX(x);
	m_texture->setX(x);
}


void UITextureElement::setY(int y) {
	UIElement::setY(y);
	m_texture->setY(y);
}

void UITextureElement::setColor(u32 color)
{
	m_texture->setColor(color);
}

u32 UITextureElement::getColor()
{
	return m_texture->getColor();
}

/*
 * UITextureElement.cpp
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#include "UITextureElement.h"

UITextureElement::UITextureElement(int x, int y, float width, float height,
		const char* name, BasicTexture* tex) : UIElement( x, y, width, height, name ), m_texture(tex) {


}

UITextureElement::~UITextureElement()
{
}

void UITextureElement::load()

{
}

void UITextureElement::unload()
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

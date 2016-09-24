/*
 * UITextureElement.cpp
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

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

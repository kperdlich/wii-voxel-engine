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

#include <math.h>
#include "BasicButton.h"
#include "../Controller.h"
#include "../utils/Debug.h"
#include "../core/grrlib.h"

BasicButton::BasicButton( float x, float y, const char* name, Texture* defaultTexture, Texture* highlightTexture, LabelTexture* label, OnClickCallback clickCallback  ) : m_label( label ), m_highlightTexture( highlightTexture ), m_clickCallback( clickCallback ), UITextureElement( x, y, name, defaultTexture )
{
	m_texture->SetX( x );
	m_texture->SetY( y );
	m_highlightTexture->SetX( x );
	m_highlightTexture->SetY( y );
	m_highlightTexture->SetVisible(false);
	UpdateLabel();
}

BasicButton::~BasicButton() { }


void BasicButton::Update()
{
	if ( HandleMoveOver() )
	{
		HandleOnClick();
	}
}

bool BasicButton::HandleMoveOver() {

	WiiPad* pad = Controller::GetInstance().GetInputHandler().GetPadByID( WII_PAD_0 );
	bool mouseOver = GRRLIB_PtInRect(m_texture->GetX(), m_texture->GetY(), m_texture->GetWidth(), m_texture->GetHeight(), pad->GetX(), pad->GetY() );
	m_texture->SetVisible(!mouseOver);
	m_highlightTexture->SetVisible(mouseOver);
	return mouseOver;
}

void BasicButton::HandleOnClick() {

	WiiPad* pad = Controller::GetInstance().GetInputHandler().GetPadByID( WII_PAD_0 );

	if ( (pad->ButtonsUp() & WPAD_BUTTON_A) && m_clickCallback )
	{
		m_clickCallback(this);
	}
}

void BasicButton::SetColor(u32 color)
{
	UITextureElement::SetColor(color);
	m_highlightTexture->SetColor(color);

}

void BasicButton::SetButtonCallback(OnClickCallback callback)
{
	m_clickCallback = callback;
}

void BasicButton::UpdateLabel()
{
	uint32_t newFontSize = m_texture->GetHeight() - (2*BUTTON_LABEL_DISTANCE);
	m_label->setFontSize( newFontSize );
	m_label->SetY( m_texture->GetY() + BUTTON_LABEL_DISTANCE );

	uint32_t textWidthInPixel = GRRLIB_WidthTTF(&m_label->getFont(), m_label->getText(), m_label->getFontSize());
	m_label->SetX(m_texture->GetX() + (( m_texture->GetWidth() / 2) - (textWidthInPixel / 2)));
}


void BasicButton::SetX(uint32_t x)
{
	UITextureElement::SetX(x);
	m_highlightTexture->SetX(x);
	UpdateLabel();

}

void BasicButton::SetY(uint32_t y)
{
	UITextureElement::SetY(y);
	m_highlightTexture->SetY(y);
	UpdateLabel();
}

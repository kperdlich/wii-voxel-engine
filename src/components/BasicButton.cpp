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
#include "../Engine.h"
#include "../utils/Debug.h"
#include "../core/grrlib.h"

constexpr int BUTTON_LABEL_DISTANCE = 3;

BasicButton::BasicButton(float x, float y, const char* name, Sprite* defaultTexture,
                          Sprite* highlightTexture, Label* label, ButtonCallback clickCallback)
    : m_label(label), m_highlightTexture(highlightTexture), m_clickCallback(clickCallback), UiTextureElement(x, y, name, defaultTexture)
{
    m_sprite->SetX(x);
    m_sprite->SetY(y);
    m_highlightTexture->SetX(x);
    m_highlightTexture->SetY(y);
	m_highlightTexture->SetVisible(false);
	UpdateLabel();
}

BasicButton::~BasicButton()
{
    if (m_highlightTexture)
        delete m_highlightTexture;
    if (m_label)
        delete m_label;
}


void BasicButton::Update()
{
    if (MouseOver())
	{
        CheckForClick();
	}
}

bool BasicButton::MouseOver()
{
    WiiPad* pad = Engine::Get().GetInputHandler().GetPadByID(WII_PAD_0);
    bool mouseOver = GRRLIB_PtInRect(m_sprite->GetX(), m_sprite->GetY(), m_sprite->GetWidth(), m_sprite->GetHeight(), pad->GetX(), pad->GetY() );
    if (mouseOver != m_mouseOver)
    {
        m_sprite->SetVisible(!mouseOver);
        m_highlightTexture->SetVisible(mouseOver);
        Engine::Get().GetSpriteStageManager().SetSpriteCashDirty(true);
        m_mouseOver = mouseOver;
    }

	return mouseOver;
}

void BasicButton::CheckForClick()
{
    WiiPad* pad = Engine::Get().GetInputHandler().GetPadByID(WII_PAD_0);

    if ((pad->ButtonsUp() & WPAD_BUTTON_A) && m_clickCallback)
	{
		m_clickCallback(this);
	}
}

void BasicButton::SetColor(u32 color)
{
	UiTextureElement::SetColor(color);
	m_highlightTexture->SetColor(color);

}

void BasicButton::SetButtonCallback(ButtonCallback callback)
{
	m_clickCallback = callback;
}

void BasicButton::UpdateLabel()
{
    uint32_t newFontSize = m_sprite->GetHeight() - (2*BUTTON_LABEL_DISTANCE);
	m_label->SetFontSize( newFontSize );
    m_label->SetY(m_sprite->GetY() + BUTTON_LABEL_DISTANCE);

    uint32_t textWidthInPixel = GRRLIB_WidthTTF(&m_label->GetFont(), m_label->GetText().c_str(), m_label->GetFontSize());
    m_label->SetX(m_sprite->GetX() + (( m_sprite->GetWidth() / 2) - (textWidthInPixel / 2)));
}


void BasicButton::SetX(uint32_t x)
{
	UiTextureElement::SetX(x);
	m_highlightTexture->SetX(x);
	UpdateLabel();

}

void BasicButton::SetY(uint32_t y)
{
	UiTextureElement::SetY(y);
	m_highlightTexture->SetY(y);
	UpdateLabel();
}

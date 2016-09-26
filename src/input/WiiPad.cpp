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


/**
 *
 * Note:
 * 	WPAD_ButtonsDown & WPAD_BUTTON_RIGHT = right arrow key
 * 	WPAD_ButtonsDown & WPAD_BUTTON_left = right arrow key
 *
 * 	WPAD_ButtonsHeld & WPAD_BUTTON_A = left mouse btn
 * 	WPAD_ButtonsHeld & WPAD_BUTTON_B = right mouse btn
 *
 *
 */
#include "WiiPad.h"
#include "../core/grrlib.h"


WiiPad::WiiPad( int chanID ) : m_ChanID( chanID )
{
	WPAD_SetVRes(chanID, rmode->fbWidth, rmode->xfbHeight);
	WPAD_SetDataFormat(chanID, WPAD_FMT_BTNS_ACC_IR);
}

WiiPad::~WiiPad() { }

void WiiPad::Update()
{
	m_Data = WPAD_Data( m_ChanID );
	m_ButtonDown = WPAD_ButtonsDown( m_ChanID );
	m_ButtonHeld = WPAD_ButtonsHeld( m_ChanID );
	m_ButtonUp = WPAD_ButtonsUp( m_ChanID );
}

float WiiPad::GetX() const {
	return m_Data->ir.x;
}

float WiiPad::GetY() const {
	return m_Data->ir.y;
}

u32 WiiPad::ButtonsDown() const {
	return m_ButtonDown;
}

u32 WiiPad::ButtonsHeld() const {
	return m_ButtonHeld;
}

u32 WiiPad::ButtonsUp() const {
	return m_ButtonUp;
}

const WPADData* WiiPad::GetData() const {
	return m_Data;
}

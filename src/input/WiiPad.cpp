/*
 * WiiPad.cpp
 *
 *  Created on: 30.05.2015
 *      Author: Kevin
 */


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

void WiiPad::update()
{
	m_Data = WPAD_Data( m_ChanID );
	m_ButtonDown = WPAD_ButtonsDown( m_ChanID );
	m_ButtonHeld = WPAD_ButtonsHeld( m_ChanID );
	m_ButtonUp = WPAD_ButtonsUp( m_ChanID );
}

float WiiPad::getX() {
	return m_Data->ir.x;
}

float WiiPad::getY() {
	return m_Data->ir.y;
}

u32 WiiPad::buttonsDown() {
	return m_ButtonDown;
}

u32 WiiPad::buttonsHeld() {
	return m_ButtonHeld;
}

u32 WiiPad::ButtonsUp() {
	return m_ButtonUp;
}

WPADData* WiiPad::getData() {
	return m_Data;
}

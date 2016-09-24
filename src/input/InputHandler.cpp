/*
 * InputHandler.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#include "InputHandler.h"

InputHandler::InputHandler() {
}

InputHandler::~InputHandler() {
	for (uint i = 0; i < m_pads.size(); i++)
	{
		delete m_pads[i];
	}
}

void InputHandler::Init() {
	WPAD_Init();
	m_pads.push_back( new WiiPad( WPAD_CHAN_0 ) ); // only one because of singleplayer ;)
}


void InputHandler::Update() {
	WPAD_SetVRes(0, 640, 480);
	WPAD_ScanPads();
	for (uint i = 0; i < m_pads.size(); i++)
	{
		static_cast<WiiPad*>(m_pads[ i ] )->Update();
	}
}

WiiPad* InputHandler::GetPadByID(uint padID) {
	if ( padID >= 0 && padID < m_pads.size() )
	{
		return m_pads[ padID ];
	}

	return NULL;
}

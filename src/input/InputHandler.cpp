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

#include "InputHandler.h"
#include "../utils/Debug.h"

InputHandler::InputHandler() {
}

InputHandler::~InputHandler()
{
    for (uint32_t i = 0; i < m_pads.size(); i++)
	{
		delete m_pads[i];
	}
}

void InputHandler::Init()
{
	WPAD_Init();
	m_pads.push_back( new WiiPad( WPAD_CHAN_0 ) ); // only one because of singleplayer ;)

    LOG("Wiipad initialized");
}


void InputHandler::Update()
{
	WPAD_SetVRes(0, 640, 480);
	WPAD_ScanPads();
    for (uint32_t i = 0; i < m_pads.size(); i++)
	{
		static_cast<WiiPad*>(m_pads[ i ] )->Update();
	}
}

WiiPad* InputHandler::GetPadByID(uint32_t padID)
{
	if ( padID >= 0 && padID < m_pads.size() )
	{
		return m_pads[ padID ];
	}

    return nullptr;
}

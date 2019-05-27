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

#pragma once

#include <vector>
#include "../input/WiiPad.h"

#define WII_PAD_0 0
#define WII_PAD_1 1
#define WII_PAD_2 2
#define WII_PAD_3 3


class InputHandler {

private:
	std::vector< WiiPad* > m_pads;

public:
	~InputHandler();
	InputHandler();
	void Init();
	void Update();
    WiiPad* GetPadByID( uint32_t padID );
};


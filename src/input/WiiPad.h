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

#ifndef _WIIPAD_H_
#define _WIIPAD_H_

#include <wiiuse/wpad.h>

class WiiPad {

private:
	WPADData* m_Data;
	int m_ChanID;
	u32 m_ButtonDown;
	u32 m_ButtonHeld;
	u32 m_ButtonUp;
public:
	WiiPad( int chanID );
	virtual ~WiiPad();
	void Update();
	float GetX() const;
	float GetY() const;
	float GetNunchukAngleY() const;
	float GetNunchukAngleX() const;
	u32 ButtonsDown() const;
	u32 ButtonsHeld() const;
	u32 ButtonsUp() const;
	const WPADData* GetData() const;
};

#endif /* _WIIPAD_H_ */

/*
 * WiiPad.h
 *
 *  Created on: 30.05.2015
 *      Author: Kevin
 */

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
	u32 ButtonsDown() const;
	u32 ButtonsHeld() const;
	u32 ButtonsUp() const;
	const WPADData* GetData() const;
};

#endif /* _WIIPAD_H_ */

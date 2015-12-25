/*
 * WiiPad.h
 *
 *  Created on: 30.05.2015
 *      Author: Kevin
 */

#ifndef SRC_INPUT_WIIPAD_H_
#define SRC_INPUT_WIIPAD_H_

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
	void update();
	float getX();
	float getY();
	u32 buttonsDown();
	u32 buttonsHeld();
	u32 ButtonsUp();
	WPADData* getData();
};

#endif /* SRC_INPUT_WIIPAD_H_ */

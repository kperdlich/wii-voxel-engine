/*
 * InputHandler.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

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
	WiiPad* GetPadByID( uint padID );
};


#endif /* _INPUTHANDLER_H_ */

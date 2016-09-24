/*
 * Cursor.cpp
 *
 *  Created on: 28.06.2015
 *      Author: Kevin
 */

#include "Cursor.h"
#include "../Controller.h"
#include "../utils/Debug.h"

#ifdef DEBUG
	static char* cursorPositionLogBuffer;
#endif

Cursor::Cursor( const char* name, BasicTexture* tex ) : UITextureElement( 0, 0, name, tex ) {

	SetX( rmode->viWidth / 2 );
	SetY( rmode->viHeight / 2 );

#ifdef DEBUG
	cursorPositionLogBuffer = new char[50];
#endif
}


Cursor::~Cursor() {

#ifdef DEBUG
	delete [] cursorPositionLogBuffer;
#endif

}

void Cursor::Update() {

	WiiPad* pad = Controller::GetInstance().GetInputHandler().GetPadByID( WII_PAD_0 );

#ifdef DEBUG
	sprintf(cursorPositionLogBuffer, "Cursor x: %d y: %d", (int)pad->GetX(), (int) pad->GetY());
	Debug::GetInstance().Log( cursorPositionLogBuffer );
#endif

	SetX( pad->GetX());
	SetY( pad->GetY());
}

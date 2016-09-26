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

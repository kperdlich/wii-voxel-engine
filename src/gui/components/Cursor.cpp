/*
 * Cursor.cpp
 *
 *  Created on: 28.06.2015
 *      Author: Kevin
 */

#include "Cursor.h"
#include "../../handler/Controller.h"
#include "../../utils/Debug.h"

Cursor::Cursor( const char* name, BasicTexture* tex ) : UITextureElement( 0, 0, name, tex ) {

	setX( rmode->viWidth / 2 );
	setY( rmode->viHeight / 2 );
}

Cursor::~Cursor() {


}

void Cursor::update() {

	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );

#ifdef DEBUG
	char* bufferXY = new char[100];
	sprintf(bufferXY, "Cursor x: %d y: %d", (int)pad->getX(), (int) pad->getY());
	Debug::getInstance().log( bufferXY );
#endif

	setX( pad->getX());
	setY( pad->getY());
}

void Cursor::setColor(u32 color) {
	m_texture->setColor(color);
}

u32 Cursor::getColor() {
	return m_texture->getColor();

}

/*
 * Cursor.cpp
 *
 *  Created on: 28.06.2015
 *      Author: Kevin
 */

#include "Cursor.h"
#include "../../handler/Controller.h"
#include "../../utils/Debug.h"

Cursor::Cursor( const char* name, BasicTexture* tex ) : UITextureElement( 0, 0, 0, 0, name, tex ) {

	m_texture->setX( (rmode->viWidth / 2) - (m_texture->getWidth() / 2) );
	m_texture->setY( (rmode->viHeight / 2) - ( m_texture->getHeight() / 2 ) );
}

Cursor::~Cursor() {


}

void Cursor::update() {

	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );

	char* bufferXY = new char[100];
	sprintf(bufferXY, "cursor x: %d y: %d", (int)pad->getX(), (int) pad->getY());
	Debug::getInstance().log( bufferXY );

	m_texture->setX( pad->getX() );
	m_texture->setY( pad->getY() );


	if ( pad->buttonsDown() & WPAD_BUTTON_A)
	{
		char* bufferClick = new char[100];
		sprintf(bufferClick, "Push A Button" );
		Debug::getInstance().log( bufferClick );
	}

}

void Cursor::setColor(u32 color) {
	m_texture->setColor(color);
}

u32 Cursor::getColor() {
	return m_texture->getColor();

}

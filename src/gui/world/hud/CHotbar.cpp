/*
 * CHotbar.cpp
 *
 *  Created on: 09.07.2015
 *      Author: Kevin
 */

#include "CHotbar.h"

CHotbar::CHotbar( const char* name, BasicTexture* tex ) : UITextureElement(0, 0, 0, 0, name, tex ) {

	tex->setX( (rmode->viWidth / 2) - (m_texture->getWidth() / 2) );
	tex->setY( rmode->viHeight - m_texture->getHeight() );

}

CHotbar::~CHotbar() {
}

void CHotbar::setColor(u32 color) {
	m_texture->setColor( color );
}

u32 CHotbar::getColor() {
	return m_texture->getColor();
}

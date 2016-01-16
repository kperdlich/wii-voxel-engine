/*
 * Logo.cpp
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#include "Logo.h"


Logo::Logo(const char* name,
		BasicTexture* tex) : UITextureElement(0, 0, name, tex) {

	m_texture->setX( (rmode->viWidth / 2) - (m_texture->getWidth() / 2) );
	m_texture->setY( (rmode->viHeight / 2) - ( m_texture->getHeight() / 2 ) );
}

Logo::~Logo() {
}

void Logo::load() {
}

void Logo::unload() {
}

void Logo::setColor(u32 color) {
	m_texture->setColor(color);
}

u32 Logo::getColor() {
	return m_texture->getColor();
}

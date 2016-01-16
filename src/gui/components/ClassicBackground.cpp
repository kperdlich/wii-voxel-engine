/*
 * ClassicBackground.cpp
 *
 *  Created on: 27.06.2015
 *      Author: Kevin
 */

#include "ClassicBackground.h"
#include "../../handler/Controller.h"

ClassicBackground::ClassicBackground(const char* name, BasicTexture* tex) :
	UITextureElement(0, 0, name, tex ) {

}

ClassicBackground::~ClassicBackground() {

}


void ClassicBackground::load() {

}

void ClassicBackground::unload() {
}

void ClassicBackground::setColor(u32 color) {
	m_texture->setColor(color);

}

u32 ClassicBackground::getColor() {
	return m_texture->getColor();
}

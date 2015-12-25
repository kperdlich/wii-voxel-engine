/*
 * BasicTexture.cpp
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#include "BasicTexture.h"
#include "ColorHelper.h"

BasicTexture::BasicTexture( float x, float y, const u16 id ) : m_x(x), m_y(y), m_id(id) {
	m_color = GRRLIB_WHITE;
}

BasicTexture::~BasicTexture() {
}


float BasicTexture::getX() {
	return m_x;
}

void BasicTexture::setX(float x) {
	m_x = x;
}

float BasicTexture::getY() {
	return m_y;
}

void BasicTexture::setY(float y) {
	m_y = y;
}

u16 BasicTexture::getId() {
	return m_id;
}

txTypes BasicTexture::getTextureType() {
	return INVALID;
}

void BasicTexture::loadTexture() {
}

void BasicTexture::unloadTexture() {
}

bool BasicTexture::isVisible() {
	return false;
}

void BasicTexture::setColor(u32 color) {
	m_color = color;
}

u32 BasicTexture::getColor() {
	return m_color;
}

void BasicTexture::setVisible( bool value ) {
	m_visible = value;
}

uint BasicTexture::getWidth() {
	return 0;
}

uint BasicTexture::getHeight() {
	return 0;
}

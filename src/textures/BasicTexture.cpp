/*
 * BasicTexture.cpp
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#include "BasicTexture.h"
#include "../utils/ColorHelper.h"

BasicTexture::BasicTexture( float x, float y, u16 id ) : m_x(x), m_y(y), m_id(id) {
	m_color = GRRLIB_WHITE;
}

BasicTexture::~BasicTexture() {
}


float BasicTexture::GetX() const
{
	return m_x;
}

void BasicTexture::SetX(float x) {
	m_x = x;
}

float BasicTexture::GetY() const
{
	return m_y;
}

void BasicTexture::SetY(float y) {
	m_y = y;
}

u16 BasicTexture::GetId() const
{
	return m_id;
}

txTypes BasicTexture::GetTextureType() const
{
	return INVALID;
}

void BasicTexture::LoadTexture() {}

void BasicTexture::UnloadTexture() {}

bool BasicTexture::IsVisible() const
{
	return false;
}

void BasicTexture::SetColor(u32 color)
{
	m_color = color;
}

u32 BasicTexture::GetColor() const
{
	return m_color;
}

void BasicTexture::SetVisible( bool value )
{
	m_visible = value;
}

uint BasicTexture::GetWidth() const
{
	return 0;
}

uint BasicTexture::GetHeight() const
{
	return 0;
}

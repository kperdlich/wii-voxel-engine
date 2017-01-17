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

#include "BasicTexture.h"
#include "../utils/ColorHelper.h"

BasicTexture::BasicTexture( float x, float y, uint16_t id ) : m_x(x), m_y(y), m_id(id) {
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

uint16_t BasicTexture::GetId() const
{
	return m_id;
}

ETextureType BasicTexture::GetTextureType() const
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

uint32_t BasicTexture::GetColor() const
{
	return m_color;
}

void BasicTexture::SetVisible( bool value )
{
	m_bVisible = value;
}

uint32_t BasicTexture::GetWidth() const
{
	return 0;
}

uint32_t BasicTexture::GetHeight() const
{
	return 0;
}

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

#include "Vector3f.h"

Vector3f::Vector3f( float x, float y, float z ) : m_x(x), m_y(y), m_z(z) {


}

Vector3f::Vector3f() : m_x(0), m_y(0), m_z(0) {
}

Vector3f::~Vector3f() { }

float Vector3f::GetX() const {
	return m_x;
}

void Vector3f::SetX(float x) {
	m_x = x;
}

float Vector3f::GetY() const  {
	return m_y;
}

void Vector3f::SetY(float y) {
	m_y = y;
}

float Vector3f::GetZ() const {
	return m_z;
}

void Vector3f::SetZ(float z) {
	m_z = z;
}

Vector3f Vector3f::Forward()
{
	return Vector3f(0, 0, -1);
}

Vector3f Vector3f::Backward()
{
	return Vector3f(0, 0, 1);
}

Vector3f Vector3f::Left()
{
	return Vector3f( 1, 0, 0 );
}

Vector3f Vector3f::Right()
{
	return Vector3f( -1, 0, 0 );
}



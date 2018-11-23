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

#include "Vector3.h"
#include <altivec.h>

Vector3::Vector3( const Vector3& vec) : m_x(vec.GetX()), m_y(vec.GetY()), m_z(vec.GetZ()) {}

Vector3::Vector3( double x, double y, double z ) : m_x(x), m_y(y), m_z(z) {}

Vector3::Vector3() : m_x(0), m_y(0), m_z(0) {
}

Vector3::~Vector3() { }

double Vector3::GetX() const
{
	return m_x;
}

void Vector3::SetX(double x)
{
	m_x = x;
}

double Vector3::GetY() const
{
	return m_y;
}

void Vector3::SetY(double y)
{
	m_y = y;
}

double Vector3::GetZ() const
{
	return m_z;
}

void Vector3::SetZ(double z)
{
	m_z = z;
}

Vector3 Vector3::Forward()
{
	return Vector3(0, 0, -1);
}

Vector3 Vector3::Backward()
{
	return Vector3(0, 0, 1);
}

Vector3 Vector3::Left()
{
	return Vector3( 1, 0, 0 );
}

Vector3 Vector3::Right()
{
    return Vector3( -1, 0, 0 );
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	// PowerPC AltiVec
	/*float a[4] __attribute__((aligned(16))) = { m_x, m_y, m_z, .0f };
	float b[4] __attribute__((aligned(16))) = { vec.m_x, vec.m_y, vec.m_z, .0f };
	float c[4] __attribute__((aligned(16)));

	vector float *va = (vector float *) a;
	vector float *vb = (vector float *) b;
	vector float *vc = (vector float *) c;

	 *vc = vec_add(*va, *vb);

	 m_x = c[0];
	 m_y = c[1];
	 m_z = c[2];

	 return *this;
	 */

	m_x += vec.m_x;
	m_y += vec.m_y;
	m_z += vec.m_z;

    return *this;
}

Vector3 operator-(const Vector3 &lvec, const Vector3 &rvec)
{
    return Vector3(lvec.m_x - rvec.m_x, lvec.m_y - rvec.m_y, lvec.m_z - rvec.m_z);
}

Vector3 operator+(const Vector3& lvec, const Vector3& rvec )
{
	Vector3 vec(lvec.m_x, lvec.m_y, lvec.m_z );
	return vec += rvec;
}



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

#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_

class Vector3f {
public:
	Vector3f( float x, float y, float z );
	Vector3f();
	virtual ~Vector3f();

	float GetX() const;
	void SetX(float x);
	float GetY() const;
	void SetY(float y);
	float GetZ() const;
	void SetZ(float z);


	static Vector3f Forward();
	static Vector3f Backward();
	static Vector3f Left();
	static Vector3f Right();

private:
	float m_x, m_y, m_z;

};

#endif /* _VECTOR3F_H_ */

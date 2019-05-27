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

#pragma once

class Vector3 {
public:
    Vector3(const Vector3& vec);
    Vector3(double x, double y, double z);
	Vector3();
	virtual ~Vector3();

	double GetX() const;
	void SetX(double x);
	double GetY() const;
	void SetY(double y);
	double GetZ() const;
	void SetZ(double z);

	static Vector3 Forward();
	static Vector3 Backward();
	static Vector3 Left();
	static Vector3 Right();

    bool operator==(const Vector3 &vec) const
    {        
        return (m_x == vec.m_x) && (m_y == vec.m_y) && (m_z == vec.m_z);
    }

    bool operator!=(const Vector3 &vec) const
    {
        return (m_x != vec.m_x) || (m_y != vec.m_y) || (m_z != vec.m_z);
    }

	Vector3& operator+=(const Vector3& vec);


	friend Vector3 operator+(const Vector3& lvec, const Vector3& rvec );
    friend Vector3 operator-(const Vector3& lvec, const Vector3& rvec );



private:
	double m_x, m_y, m_z;

};

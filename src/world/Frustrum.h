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

class Frustrum {
public:
	Frustrum();
    ~Frustrum();

	bool CubeInFrustum( float x1, float y1, float z1, float x2, float y2, float z2  );
	bool SphereInFrustum(float x, float y, float z, float radius);
	bool PointInFrustum(float x, float y, float z);
	void CalculateFrustum();
	void NormalizePlane(float frustum[6][4], int side);

	static Frustrum& Instance();


	enum sides
	{
		RIGHT = 0,
		LEFT,
		BOTTOM,
		TOP,
		BACK,
		FRONT
	};

	enum corners
	{
		A = 0,
		B,
		C,
		D,
	};


private:
	float m_Frustum[6][4];

	float proj[16];
	float modl[16];
	float clip[16];


};

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

#include <math.h>
#include <cmath>
#include "Vector3.h"

constexpr double PI = 3.14159265;
constexpr double DEGREE_TO_RADIANS = PI / 180;

class MathHelper {

private:
	MathHelper();
public:
	virtual ~MathHelper();
    MathHelper(const MathHelper&) = delete;
    MathHelper(MathHelper&&) = delete;
    void operator=(const MathHelper&) = delete;
    void operator=(MathHelper&&) = delete;

	static Vector3 CalculateNewWorldPositionByRotation( const Vector3& rotation, const Vector3& currentWorldPosition, const Vector3& directionVector );
	static Vector3 CalculateNewWorldPositionByRotation( const Vector3& rotation, const Vector3& currentWorldPosition, float direction );
	static Vector3 CalculateNewWorldPositionByRotation( float rotation, const Vector3& currentWorldPosition, const Vector3& directionVector );
	static Vector3 CalculateNewWorldPositionByRotation( float rotation, const Vector3& currentWorldPosition, float direction );

	static double Clamp(double value, double minValue, double maxValue);
    static double Min(double value1, double value2 );
    static double Max(double value1, double value2 );
    static double Mod(double x, double y);
};

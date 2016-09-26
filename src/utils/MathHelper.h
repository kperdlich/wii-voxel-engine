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

#ifndef _MATHHELPER_H_
#define _MATHHELPER_H_

#include <math.h>
#include <cmath>
#include "Vector3f.h"

#define PI 3.14159265
#define DEGREE_TO_RADIANS PI / 180

class MathHelper {

private:
	MathHelper();
public:
	virtual ~MathHelper();
	static Vector3f CalculateNewWorldPositionByRotation( const Vector3f& rotation, const Vector3f& currentWorldPosition, float smoothFactor, const Vector3f& movementVector );
	static Vector3f CalculateNewWorldPositionByRotation( float rotation, const Vector3f& currentWorldPosition, float smoothFactor, const Vector3f& movementVector );
	static float Clamp(float value, float minValue, float maxValue);
	inline static float Min(float value1, float value2 );
	inline static float Max(float value1, float value2 );
};

#endif /* _MATHHELPER_H_ */

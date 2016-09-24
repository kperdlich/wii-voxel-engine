/*
 * MathHelper.h
 *
 *  Created on: 05.08.2015
 *      Author: Kevin
 */

#ifndef _MATHHELPER_H_
#define _MATHHELPER_H_

#include <math.h>
#include <cmath>
#include "Vector3f.h"

#define PI 3.14159265
#define DEGREE_TO_RADIANS PI / 180

class MathHelper {
public:
	MathHelper();
	virtual ~MathHelper();
	static Vector3f CalculateNewWorldPositionByCotation( const Vector3f& rotation, const Vector3f& currentWorldPosition, float smoothFactor, const Vector3f& movementVector );
	static Vector3f CalculateNewWorldPositionByRotation( float rotation, Vector3f currentWorldPosition, float smoothFactor, Vector3f movementVector );
	static float Clamp(float value, float minValue, float maxValue);
	inline static float Min(float value1, float value2 );
	inline static float Max(float value1, float value2 );
};

#endif /* _MATHHELPER_H_ */

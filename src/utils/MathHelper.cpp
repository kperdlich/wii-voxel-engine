/*
 * MathHelper.cpp
 *
 *  Created on: 05.08.2015
 *      Author: Kevin
 */

#include "MathHelper.h"

MathHelper::MathHelper() { }

MathHelper::~MathHelper() { }

Vector3f MathHelper::calculateNewWorldPositionByRotation(float rotation, Vector3f currentWorldPosition, float smoothFactor, Vector3f movementVector)
{
	float rotationInRadians = rotation * DEGREE_TO_RADIANS;
	float x = currentWorldPosition.GetX() + ( sin(rotationInRadians) * smoothFactor * movementVector.GetZ());
	float y = currentWorldPosition.GetY(); // todo add y axis movement
	float z = currentWorldPosition.GetZ() + ( cos(rotationInRadians) * smoothFactor * movementVector.GetZ()) ;
	return Vector3f(x, y, z);

}


float MathHelper::Clamp(float value, float minValue, float maxValue)
{
	return max(minValue, min(value, maxValue));
}

inline float MathHelper::min(float value1, float value2 )
{
	return (value1 < value2) ? (value1) : (value2);
}

inline float MathHelper::max(float value1, float value2 )
{
	return (value1 > value2) ? (value1) : (value2);
}

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
	float x = currentWorldPosition.getX() + ( sin(rotationInRadians) * smoothFactor * movementVector.getZ());
	float y = 0; // todo add y axis movement
	float z = currentWorldPosition.getZ() + ( cos(rotationInRadians) * smoothFactor * movementVector.getZ()) ;
	return Vector3f(x, y, z);

}

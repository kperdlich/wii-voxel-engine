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

#include "MathHelper.h"

MathHelper::MathHelper() { }

MathHelper::~MathHelper() { }

Vector3f MathHelper::CalculateNewWorldPositionByRotation(const Vector3f& rotation, const Vector3f& currentWorldPosition, const Vector3f& directionVector)
{
	float rotationYInRadians = rotation.GetY() * DEGREE_TO_RADIANS;
	float rotationXInRadians = rotation.GetX() * DEGREE_TO_RADIANS;
	float x = currentWorldPosition.GetX() + (sin(rotationYInRadians) * directionVector.GetX());
	float y = currentWorldPosition.GetY() + (sin(rotationXInRadians) * directionVector.GetY());
	float z = currentWorldPosition.GetZ() + (cos(rotationYInRadians) * directionVector.GetZ()) ;
	return Vector3f(x, y, z);
}

Vector3f MathHelper::CalculateNewWorldPositionByRotation( const Vector3f& rotation, const Vector3f& currentWorldPosition, float direction)
{
	float rotationYInRadians = rotation.GetY() * DEGREE_TO_RADIANS;
	float rotationXInRadians = rotation.GetX() * DEGREE_TO_RADIANS;
	float x = currentWorldPosition.GetX() + (sin(rotationYInRadians) * direction);
	float y = currentWorldPosition.GetY() + (sin(rotationXInRadians) * direction);
	float z = currentWorldPosition.GetZ() + (cos(rotationYInRadians) * direction);
	return Vector3f(x, y, z);
}

Vector3f MathHelper::CalculateNewWorldPositionByRotation(float rotation, const Vector3f& currentWorldPosition, const Vector3f& directionVector)
{
	float rotationInRadians = rotation * DEGREE_TO_RADIANS;
	float x = currentWorldPosition.GetX() + (sin(rotationInRadians) * directionVector.GetX());
	float y = currentWorldPosition.GetY() + (sin(rotationInRadians) * directionVector.GetY());
	float z = currentWorldPosition.GetZ() + (cos(rotationInRadians) * directionVector.GetZ());
	return Vector3f(x, y, z);
}

Vector3f MathHelper::CalculateNewWorldPositionByRotation( float rotation, const Vector3f& currentWorldPosition, float direction)
{
	float rotationInRadians = rotation * DEGREE_TO_RADIANS;
	float x = currentWorldPosition.GetX() + (sin(rotationInRadians) * direction);
	float y = currentWorldPosition.GetY() + (sin(rotationInRadians) * direction);
	float z = currentWorldPosition.GetZ() + (cos(rotationInRadians) * direction);
	return Vector3f(x, y, z);
}


float MathHelper::Clamp(float value, float minValue, float maxValue)
{
	return Max(minValue, Min(value, maxValue));
}

inline float MathHelper::Min(float value1, float value2 )
{
	return (value1 < value2) ? (value1) : (value2);
}

inline float MathHelper::Max(float value1, float value2 )
{
	return (value1 > value2) ? (value1) : (value2);
}

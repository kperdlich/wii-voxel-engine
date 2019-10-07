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

#include "utils/MathHelper.h"

MathHelper::MathHelper() { }

MathHelper::~MathHelper() { }

Vector3 MathHelper::CalculateNewWorldPositionByRotation(const Vector3& rotation, const Vector3& currentWorldPosition, const Vector3& directionVector)
{
    float rotationYInRadians = rotation.GetY() * DEGREE_TO_RADIANS;
    float rotationXInRadians = rotation.GetX() * DEGREE_TO_RADIANS;
    double x = currentWorldPosition.GetX() + (sin(rotationYInRadians) * directionVector.GetX());
    double y = currentWorldPosition.GetY() + (sin(rotationXInRadians) * directionVector.GetY());
    double z = currentWorldPosition.GetZ() + (cos(rotationYInRadians) * directionVector.GetZ()) ;
	return Vector3(x, y, z);
}

Vector3 MathHelper::CalculateNewWorldPositionByRotation( const Vector3& rotation, const Vector3& currentWorldPosition, float direction)
{
    float rotationYInRadians = rotation.GetY() * DEGREE_TO_RADIANS;
    float rotationXInRadians = rotation.GetX() * DEGREE_TO_RADIANS;
    double x = currentWorldPosition.GetX() + (sin(rotationYInRadians) * direction);
    double y = currentWorldPosition.GetY() + (sin(rotationXInRadians) * direction);
    double z = currentWorldPosition.GetZ() + (cos(rotationYInRadians) * direction);
	return Vector3(x, y, z);
}

Vector3 MathHelper::CalculateNewWorldPositionByRotation(float rotation, const Vector3& currentWorldPosition, const Vector3& directionVector)
{
    float rotationInRadians = rotation * DEGREE_TO_RADIANS;
    double x = currentWorldPosition.GetX() + (sin(rotationInRadians) * directionVector.GetX());
    double y = currentWorldPosition.GetY() + (sin(rotationInRadians) * directionVector.GetY());
    double z = currentWorldPosition.GetZ() + (cos(rotationInRadians) * directionVector.GetZ());
	return Vector3(x, y, z);
}

Vector3 MathHelper::CalculateNewWorldPositionByRotation( float rotation, const Vector3& currentWorldPosition, float direction)
{
    float rotationInRadians = rotation * DEGREE_TO_RADIANS;
    double x = currentWorldPosition.GetX() + (sin(rotationInRadians) * direction);
    double y = currentWorldPosition.GetY() + (sin(rotationInRadians) * direction);
    double z = currentWorldPosition.GetZ() + (cos(rotationInRadians) * direction);
	return Vector3(x, y, z);
}


double MathHelper::Clamp(double value, double minValue, double maxValue)
{
	return Max(minValue, Min(value, maxValue));
}

double MathHelper::Min(double value1, double value2 )
{
	return (value1 < value2) ? (value1) : (value2);
}

double MathHelper::Max(double value1, double value2 )
{
	return (value1 > value2) ? (value1) : (value2);
}

double MathHelper::Mod(double x, double y)
{
    return x-y*floor(x/y);
}

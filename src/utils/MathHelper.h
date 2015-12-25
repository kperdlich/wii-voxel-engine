/*
 * MathHelper.h
 *
 *  Created on: 05.08.2015
 *      Author: Kevin
 */

#ifndef SRC_UTILS_MATHHELPER_H_
#define SRC_UTILS_MATHHELPER_H_

#include <math.h>
#include "Vector3f.h"

#define PI 3.14159265
#define DEGREE_TO_RADIANS PI / 180

class MathHelper {
public:
	MathHelper();
	virtual ~MathHelper();
	static Vector3f calculateNewWorldPositionByRotation( float rotation, Vector3f currentWorldPosition, float smoothFactor, Vector3f movementVector );
};

#endif /* SRC_UTILS_MATHHELPER_H_ */

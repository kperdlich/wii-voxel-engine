/*
 * CAABB.h
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#include "../../utils/Vector3f.h"

#ifndef SRC_PHYSICS_COLLISION_CAABB_H_
#define SRC_PHYSICS_COLLISION_CAABB_H_

class CAABB {
public:
	CAABB(Vector3f& vecMin, Vector3f& vecMax);
	virtual ~CAABB();

	Vector3f& GetMin();
	Vector3f& GetMax();

	bool CoolidesWith( CAABB& box );
	bool CoolidesWith( Vector3f& vecPoint);

private:
	Vector3f m_vecMin, m_vecMax;

};

#endif /* SRC_PHYSICS_COLLISION_CAABB_H_ */

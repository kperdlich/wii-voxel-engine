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

#include "../../utils/Vector3.h"

#ifndef _CAABB_H_
#define _CAABB_H_

class AABB {
public:
	AABB(Vector3& vecMin, Vector3& vecMax);
	virtual ~AABB();

	Vector3& GetMin();
	Vector3& GetMax();

	bool CoolidesWith( AABB& box );
	bool CoolidesWith( Vector3& vecPoint);

private:
	Vector3 m_vecMin, m_vecMax;

};

#endif /* _CAABB_H_ */

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

#include "../../utils/Vector3f.h"

#ifndef _CAABB_H_
#define _CAABB_H_

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

#endif /* _CAABB_H_ */

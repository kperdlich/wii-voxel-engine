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
        AABB(const Vector3& vecMin, const Vector3& vecMax);

        Vector3 GetMin() const;
        Vector3 GetMax() const;

        bool CoolidesWith( const AABB& box ) const;
        bool CoolidesWith( const Vector3& vecPoint) const;

private:
	Vector3 m_vecMin, m_vecMax;

};

#endif /* _CAABB_H_ */

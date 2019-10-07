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

#include "physics/collision/AABB.h"

AABB::AABB(const Vector3& vecMin, const Vector3& vecMax) : m_vecMin(vecMin), m_vecMax(vecMax)
{


}


bool AABB::CoolidesWith(const AABB& box) const
{
	return(m_vecMax.GetX() > box.GetMin().GetX() &&
	    m_vecMin.GetX() < box.GetMax().GetX() &&
	    m_vecMax.GetY() > box.GetMin().GetY() &&
	    m_vecMin.GetY() < box.GetMax().GetY() &&
	    m_vecMax.GetZ() > box.GetMin().GetZ() &&
	    m_vecMin.GetZ() < box.GetMax().GetZ());
}

bool AABB::CoolidesWith(const Vector3& vecPoint) const
{
	 if(vecPoint.GetX() > m_vecMin.GetX() && vecPoint.GetX() < m_vecMax.GetX() &&
			 vecPoint.GetY() > m_vecMin.GetY() && vecPoint.GetY() < m_vecMax.GetY() &&
			 vecPoint.GetZ() > m_vecMin.GetZ() && vecPoint.GetZ() < m_vecMax.GetZ())
	 {
	        return true;
	 }

	return false;
}

Vector3 AABB::GetMin() const
{
	return m_vecMin;
}

Vector3 AABB::GetMax() const
{
	return m_vecMax;
}

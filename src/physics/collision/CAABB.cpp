/*
 * CAABB.cpp
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#include "CAABB.h"

CAABB::CAABB(Vector3f& vecMin, Vector3f& vecMax) : m_vecMin(vecMin), m_vecMax(vecMax)
{


}

CAABB::~CAABB()
{

}

bool CAABB::CoolidesWith( CAABB& box )
{
	return(m_vecMax.getX() > box.GetMin().getX() &&
	    m_vecMin.getX() < box.GetMax().getX() &&
	    m_vecMax.getY() > box.GetMin().getY() &&
	    m_vecMin.getY() < box.GetMax().getY() &&
	    m_vecMax.getZ() > box.GetMin().getZ() &&
	    m_vecMin.getZ() < box.GetMax().getZ());
}

bool CAABB::CoolidesWith( Vector3f& vecPoint)
{
	 if(vecPoint.getX() > m_vecMin.getX() && vecPoint.getX() < m_vecMax.getX() &&
			 vecPoint.getY() > m_vecMin.getY() && vecPoint.getY() < m_vecMax.getY() &&
			 vecPoint.getZ() > m_vecMin.getZ() && vecPoint.getZ() < m_vecMax.getZ())
	 {
	        return true;
	 }

	return false;
}

Vector3f& CAABB::GetMin()
{
	return m_vecMin;
}

Vector3f& CAABB::GetMax()
{
	return m_vecMax;
}

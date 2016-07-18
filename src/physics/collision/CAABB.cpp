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
	return(m_vecMax.GetX() > box.GetMin().GetX() &&
	    m_vecMin.GetX() < box.GetMax().GetX() &&
	    m_vecMax.GetY() > box.GetMin().GetY() &&
	    m_vecMin.GetY() < box.GetMax().GetY() &&
	    m_vecMax.GetZ() > box.GetMin().GetZ() &&
	    m_vecMin.GetZ() < box.GetMax().GetZ());
}

bool CAABB::CoolidesWith( Vector3f& vecPoint)
{
	 if(vecPoint.GetX() > m_vecMin.GetX() && vecPoint.GetX() < m_vecMax.GetX() &&
			 vecPoint.GetY() > m_vecMin.GetY() && vecPoint.GetY() < m_vecMax.GetY() &&
			 vecPoint.GetZ() > m_vecMin.GetZ() && vecPoint.GetZ() < m_vecMax.GetZ())
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

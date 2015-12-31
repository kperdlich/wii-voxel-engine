/*
 * Camera.cpp
 *
 *  Created on: 24.07.2015
 *      Author: Kevin
 */

#include "Camera.h"
#include <grrlib.h>

Camera::Camera() : m_cam(0, 0, 0.1f), m_up(0, 1.0f, 0), m_look(0, 0, 0), m_wordScale(1.0f, 1.0f, 1.0f), m_worldAngle(0, 0, 0), m_worldPosition(0, 0, 10.0f) {
}

Camera::~Camera() {

}

void Camera::init()
{
	GRRLIB_Camera3dSettings(m_cam.getX(), m_cam.getY(), m_cam.getZ(), m_up.getX(), m_up.getY(), m_up.getZ(), m_look.getX(), m_look.getY(), m_look.getZ());
}


float Camera::getWorldPositionX() {
	return m_worldPosition.getX();
}

float Camera::getWorldPositionY() {
	return m_worldPosition.getY();
}

float Camera::getWorldPositionZ() {
	return m_worldPosition.getZ();
}

float Camera::getWorldAngleX() {
	return m_worldAngle.getX();
}

float Camera::getWorldAngleY() {
	return m_worldAngle.getY();
}

float Camera::getWorldAngleZ() {
	return m_worldAngle.getZ();
}

float Camera::getWorldScaleX() {
	return m_wordScale.getX();
}

float Camera::getWorldScaleY() {
	return m_wordScale.getY();
}

void Camera::setWorldPosititon(Vector3f position) {
	m_worldPosition.setX( position.getX() );
	m_worldPosition.setY( position.getY() );
	m_worldPosition.setZ( position.getZ() );
}

float Camera::getWorldScaleZ() {
	return m_wordScale.getZ();
}

Vector3f Camera::getWorldPosition() {
	return m_worldPosition;
}

void Camera::setWorldAngle(Vector3f angle) {

	if ( angle.getX() > 360 )
	{
		angle.setX(angle.getX() - 360);
	}
	else if(angle.getX() < -360)
	{
		angle.setX(angle.getX() + 360);
	}

	if ( angle.getY() > 360 )
	{
		angle.setY(angle.getY() - 360);
	}
	else if(angle.getY() < -360)
	{
		angle.setY(angle.getY() + 360);
	}

	if ( angle.getZ() > 360 )
	{
		angle.setZ(angle.getZ() - 360);
	}
	else if(angle.getZ() < -360)
	{
		angle.setZ(angle.getZ() + 360);
	}

	m_worldAngle.setX( angle.getX() );
	m_worldAngle.setY( angle.getY() );
	m_worldAngle.setZ( angle.getZ() );
}

Vector3f Camera::getWorldAngle() {
	return m_worldAngle;
}

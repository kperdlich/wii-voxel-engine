/*
 * Camera.cpp
 *
 *  Created on: 24.07.2015
 *      Author: Kevin
 */

#include "Camera.h"
#include <grrlib.h>

Camera::Camera() : m_cam(0, 0, 0.1f), m_up(.0f, 1.0f, .0f), m_look(0, 0, 0), m_wordScale(1.0f, 1.0f, 1.0f), m_worldAngle(0, 0, 0), m_worldPosition(0, 0, 10.0f) {
}

Camera::~Camera() {

}

void Camera::init()
{
	GRRLIB_Camera3dSettings(m_cam.getX(), m_cam.getY(), m_cam.getZ(), m_up.getX(), m_up.getY(), m_up.getZ(), m_look.getX(), m_look.getY(), m_look.getZ());
}


float Camera::getWorldPositionX() {
	return m_attachedToEntity->getPosition().getX();
}

float Camera::getWorldPositionY() {
	return m_attachedToEntity->getPosition().getY();
}

float Camera::getWorldPositionZ() {
	return m_attachedToEntity->getPosition().getZ();
}

float Camera::getWorldAngleX() {
	return m_attachedToEntity->getRotation().getX();
}

float Camera::getWorldAngleY() {
	return m_attachedToEntity->getRotation().getY();
}

float Camera::getWorldAngleZ() {
	return m_attachedToEntity->getRotation().getZ();
}

float Camera::getWorldScaleX() {
	return m_wordScale.getX();
}

float Camera::getWorldScaleY() {
	return m_wordScale.getY();
}


float Camera::getWorldScaleZ() {
	return m_wordScale.getZ();
}

Vector3f Camera::getWorldPosition() {
	return m_attachedToEntity->getPosition();
}


Vector3f Camera::getWorldAngle() {
	return m_attachedToEntity->getRotation();
}

void Camera::attachTo(Entity& entity)
{
	m_attachedToEntity = &entity;
}

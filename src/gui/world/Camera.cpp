/*
 * Camera.cpp
 *
 *  Created on: 24.07.2015
 *      Author: Kevin
 */

#include "Camera.h"
#include "../../core/grrlib.h"

Camera::Camera() : m_cam(0, 0, 0.1f), m_up(.0f, 1.0f, .0f), m_look(0, 0, 0), m_wordScale(1.0f, 1.0f, 1.0f), m_worldAngle(0, 0, 0), m_worldPosition(0, 0, 10.0f) {
}

Camera::~Camera() {

}

void Camera::init()
{
	GRRLIB_Camera3dSettings(m_cam.GetX(), m_cam.GetY(), m_cam.GetZ(), m_up.GetX(), m_up.GetY(), m_up.GetZ(), m_look.GetX(), m_look.GetY(), m_look.GetZ());
}


float Camera::getWorldPositionX() {
	return m_attachedToEntity->GetPosition().GetX();
}

float Camera::getWorldPositionY() {
	return m_attachedToEntity->GetPosition().GetY();
}

float Camera::getWorldPositionZ() {
	return m_attachedToEntity->GetPosition().GetZ();
}

float Camera::getWorldAngleX() {
	return m_attachedToEntity->getRotation().GetX();
}

float Camera::getWorldAngleY() {
	return m_attachedToEntity->getRotation().GetY();
}

float Camera::getWorldAngleZ() {
	return m_attachedToEntity->getRotation().GetZ();
}

float Camera::getWorldScaleX() {
	return m_wordScale.GetX();
}

float Camera::getWorldScaleY() {
	return m_wordScale.GetY();
}


float Camera::getWorldScaleZ() {
	return m_wordScale.GetZ();
}

Vector3f Camera::getWorldPosition() {
	return m_attachedToEntity->GetPosition();
}


Vector3f Camera::getWorldAngle() {
	return m_attachedToEntity->getRotation();
}

void Camera::attachTo(Entity& entity)
{
	m_attachedToEntity = &entity;
}

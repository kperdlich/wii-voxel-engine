/*
 * Camera.cpp
 *
 *  Created on: 24.07.2015
 *      Author: Kevin
 */

#include "Camera.h"
#include "../core/grrlib.h"

Camera::Camera() : m_cam(0, 0, 0.1f), m_up(.0f, 1.0f, .0f), m_look(0, 0, 0), m_wordScale(1.0f, 1.0f, 1.0f), m_worldAngle(0, 0, 0), m_worldPosition(0, 0, 10.0f) {
}

Camera::~Camera() {}

void Camera::Init()
{
	GRRLIB_Camera3dSettings(m_cam.GetX(), m_cam.GetY(), m_cam.GetZ(), m_up.GetX(), m_up.GetY(), m_up.GetZ(), m_look.GetX(), m_look.GetY(), m_look.GetZ());
}

float Camera::GetWorldPositionX() const
{
	return m_attachedToEntity->GetPosition().GetX();
}

float Camera::GetWorldPositionY() const
{
	return m_attachedToEntity->GetPosition().GetY();
}

float Camera::GetWorldPositionZ() const
{
	return m_attachedToEntity->GetPosition().GetZ();
}

float Camera::GetWorldAngleX() const
{
	return m_attachedToEntity->GetRotation().GetX();
}

float Camera::GetWorldAngleY() const
{
	return m_attachedToEntity->GetRotation().GetY();
}

float Camera::GetWorldAngleZ() const
{
	return m_attachedToEntity->GetRotation().GetZ();
}

float Camera::GetWorldScaleX() const
{
	return m_wordScale.GetX();
}

float Camera::GetWorldScaleY() const
{
	return m_wordScale.GetY();
}


float Camera::GetWorldScaleZ() const
{
	return m_wordScale.GetZ();
}

const Vector3f& Camera::GetWorldPosition() const
{
	return m_attachedToEntity->GetPosition();
}


const Vector3f& Camera::GetWorldAngle() const
{
	return m_attachedToEntity->GetRotation();
}

void Camera::AttachTo(Entity& entity)
{
	m_attachedToEntity = &entity;
}

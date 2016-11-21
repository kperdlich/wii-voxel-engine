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

const Vector3& Camera::GetWorldPosition() const
{
	return m_attachedToEntity->GetPosition();
}


const Vector3& Camera::GetWorldAngle() const
{
	return m_attachedToEntity->GetRotation();
}

void Camera::AttachTo(Entity& entity)
{
	m_attachedToEntity = &entity;
}

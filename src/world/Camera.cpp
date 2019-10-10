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

#include "world/Camera.h"
#include "core/grrlib.h"


Camera::Camera()
	: m_cam(0, 0, 0.1f), m_up(.0f, 1.0f, .0f),
	m_look(0, 0, 0), m_worldPosition(10.0f, CHUNK_BLOCK_SIZE_Y, 10.0f),
	m_worldAngle(0, 0, 0),
	m_wordScale(1.0f, 1.0f, 1.0f) {}

void Camera::Init()
{
	GRRLIB_Camera3dSettings(m_cam.GetX(), m_cam.GetY(), m_cam.GetZ(), m_up.GetX(), m_up.GetY(), m_up.GetZ(), m_look.GetX(), m_look.GetY(), m_look.GetZ());
}

double Camera::GetWorldPositionX() const
{
	return m_attachedToEntity->GetPosition().GetX();
}

double Camera::GetWorldPositionY() const
{
	return m_attachedToEntity->GetPosition().GetY() + m_cameraOffset;
}

double Camera::GetWorldPositionZ() const
{
	return m_attachedToEntity->GetPosition().GetZ();
}

double Camera::GetWorldAngleX() const
{
	return m_attachedToEntity->GetRotation().GetX();
}

double Camera::GetWorldAngleY() const
{
	return m_attachedToEntity->GetRotation().GetY();
}

double Camera::GetWorldAngleZ() const
{
	return m_attachedToEntity->GetRotation().GetZ();
}

double Camera::GetWorldScaleX() const
{
	return m_wordScale.GetX();
}

double Camera::GetWorldScaleY() const
{
	return m_wordScale.GetY();
}


double Camera::GetWorldScaleZ() const
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

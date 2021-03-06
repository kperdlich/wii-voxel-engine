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

#pragma once

#include "utils/Vector3.h"
#include "entity/Entity.h"

class Camera {
public:
	Camera();
	Camera(const Camera&) = delete;
	Camera(Camera&&) = delete;
	void operator=(const Camera&) = delete;
	void operator=(Camera&&) = delete;

	void Init();

	void AttachTo(class Entity& entity);

	inline void SetCameraOffset(double value) { m_cameraOffset = value; }

	void SetWorldPosititon(Vector3 position);
	void SetWorldAngle(Vector3 angle);

	double GetWorldPositionX() const;
	double GetWorldPositionY() const;
	double GetWorldPositionZ() const;
	const Vector3& GetWorldPosition() const;

	double GetWorldAngleX() const;
	double GetWorldAngleY() const;
	double GetWorldAngleZ() const;
	const Vector3& GetWorldAngle() const;

	double GetWorldScaleX() const;
	double GetWorldScaleY() const;
	double GetWorldScaleZ() const;

private:
	Vector3 m_cam,
		m_up,
		m_look,
		m_worldPosition,
		m_worldAngle,
		m_wordScale;
	double m_cameraOffset = .0;
	Entity* m_attachedToEntity = nullptr;
};

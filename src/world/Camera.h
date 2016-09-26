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

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../utils/Vector3f.h"
#include "../entity/Entity.h"

class Camera {
public:
	Camera();
	virtual ~Camera();
	void Init();

	void AttachTo(class Entity& entity);

	void SetWorldPosititon(Vector3f position);
	void SetWorldAngle(Vector3f angle);

	float GetWorldPositionX() const;
	float GetWorldPositionY() const;
	float GetWorldPositionZ() const;
	const Vector3f& GetWorldPosition() const;

	float GetWorldAngleX() const;
	float GetWorldAngleY() const;
	float GetWorldAngleZ() const;
	const Vector3f& GetWorldAngle() const;

	float GetWorldScaleX() const;
	float GetWorldScaleY() const;
	float GetWorldScaleZ() const;


private:
	Vector3f m_cam,
			 m_up,
			 m_look,
			 m_worldPosition,
			 m_worldAngle,
			 m_wordScale;

	Entity* m_attachedToEntity = NULL;
};

#endif /* _CAMERA_H_ */

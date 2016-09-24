/*
 * Camera.h
 *
 *  Created on: 24.07.2015
 *      Author: Kevin
 */

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

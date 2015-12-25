/*
 * Camera.h
 *
 *  Created on: 24.07.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_CAMERA_H_
#define SRC_GUI_WORLD_CAMERA_H_

#include "../../utils/Vector3f.h"

class Camera {
public:
	Camera();
	virtual ~Camera();
	void init();

	/*void setCameraX( float x );
	void setCameraY( float y );
	void setCameraZ( float z );*/


	void setWorldPosititon(Vector3f position);
	void setWorldAngle(Vector3f angle);

	float getWorldPositionX();
	float getWorldPositionY();
	float getWorldPositionZ();
	Vector3f getWorldPosition();

	float getWorldAngleX();
	float getWorldAngleY();
	float getWorldAngleZ();
	Vector3f getWorldAngle();

	float getWorldScaleX();
	float getWorldScaleY();
	float getWorldScaleZ();


private:
	Vector3f m_cam,
			 m_up,
			 m_look,
			 m_worldPosition,
			 m_worldAngle,
			 m_wordScale;
};

#endif /* SRC_GUI_WORLD_CAMERA_H_ */

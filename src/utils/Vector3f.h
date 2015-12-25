/*
 * Vector3f.h
 *
 *  Created on: 24.07.2015
 *      Author: Kevin
 */

#ifndef SRC_UTILS_VECTOR3F_H_
#define SRC_UTILS_VECTOR3F_H_

class Vector3f {
public:
	Vector3f( float x, float y, float z );
	Vector3f();
	virtual ~Vector3f();

	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	float getZ();
	void setZ(float z);


	static Vector3f Forward();
	static Vector3f Backward();
	static Vector3f Left();
	static Vector3f Right();



private:
	float m_x, m_y, m_z;

};

#endif /* SRC_UTILS_VECTOR3F_H_ */

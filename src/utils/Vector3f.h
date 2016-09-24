#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_

class Vector3f {
public:
	Vector3f( float x, float y, float z );
	Vector3f();
	virtual ~Vector3f();

	float GetX() const;
	void SetX(float x);
	float GetY() const;
	void SetY(float y);
	float GetZ() const;
	void SetZ(float z);


	static Vector3f Forward();
	static Vector3f Backward();
	static Vector3f Left();
	static Vector3f Right();

private:
	float m_x, m_y, m_z;

};

#endif /* _VECTOR3F_H_ */

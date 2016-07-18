/*
 * CFrustrum.h
 *
 *  Created on: 07.06.2016
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_CFRUSTRUM_H_
#define SRC_GUI_WORLD_CFRUSTRUM_H_

class CFrustrum {
public:
	CFrustrum();
	virtual ~CFrustrum();

	bool CubeInFrustum( float x1, float y1, float z1, float x2, float y2, float z2  );
	bool SphereInFrustum(float x, float y, float z, float radius);
	bool PointInFrustum(float x, float y, float z);
	void CalculateFrustum();
	void NormalizePlane(float frustum[6][4], int side);

	static CFrustrum& Instance();


	enum sides
	{
		RIGHT = 0,
		LEFT,
		BOTTOM,
		TOP,
		BACK,
		FRONT
	};

	enum corners
	{
		A = 0,
		B,
		C,
		D,
	};


private:
	float m_Frustum[6][4];

	float proj[16];
	float modl[16];
	float clip[16];


};

#endif /* SRC_GUI_WORLD_CFRUSTRUM_H_ */

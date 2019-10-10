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

#include <math.h>
#include "world/Frustrum.h"
#include "utils/matrix4x4.h"
#include "utils/Debug.h"
#include "core/grrlib.h"

extern Mtx	_GRR_view;
extern Mtx	_ObjTransformationMtx;
extern Mtx44 _projectionMtx;

Frustrum::Frustrum() {}

Frustrum::~Frustrum() {}

bool Frustrum::CubeInFrustum(float x1, float y1, float z1, float x2, float y2, float z2)
{
	for (int i = 0; i < 6; i++)
	{
		if ((m_Frustum[i][0] * x1 + m_Frustum[i][1] * y1 + m_Frustum[i][2] * z1 + m_Frustum[i][3] <= 0.0F) &&
			(m_Frustum[i][0] * x2 + m_Frustum[i][1] * y1 + m_Frustum[i][2] * z1 + m_Frustum[i][3] <= 0.0F) &&
			(m_Frustum[i][0] * x1 + m_Frustum[i][1] * y2 + m_Frustum[i][2] * z1 + m_Frustum[i][3] <= 0.0F) &&
			(m_Frustum[i][0] * x2 + m_Frustum[i][1] * y2 + m_Frustum[i][2] * z1 + m_Frustum[i][3] <= 0.0F) &&
			(m_Frustum[i][0] * x1 + m_Frustum[i][1] * y1 + m_Frustum[i][2] * z2 + m_Frustum[i][3] <= 0.0F) &&
			(m_Frustum[i][0] * x2 + m_Frustum[i][1] * y1 + m_Frustum[i][2] * z2 + m_Frustum[i][3] <= 0.0F) &&
			(m_Frustum[i][0] * x1 + m_Frustum[i][1] * y2 + m_Frustum[i][2] * z2 + m_Frustum[i][3] <= 0.0F) &&
			(m_Frustum[i][0] * x2 + m_Frustum[i][1] * y2 + m_Frustum[i][2] * z2 + m_Frustum[i][3] <= 0.0F))
		{
			return false;
		}
	}
	return true;
}


bool Frustrum::SphereInFrustum(float x, float y, float z, float radius)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_Frustum[i][0] * x + m_Frustum[i][1] * y + m_Frustum[i][2] * z + m_Frustum[i][3] <= -radius)
		{
			return false;
		}
	}

	return true;
}

bool Frustrum::PointInFrustum(float x, float y, float z)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_Frustum[i][0] * x + m_Frustum[i][1] * y + m_Frustum[i][2] * z + m_Frustum[i][3] <= 0.0F)
		{
			return false;
		}
	}

	return true;
}

void Frustrum::CalculateFrustum()
{
	proj[0] = _projectionMtx[0][0];
	proj[1] = _projectionMtx[0][1];
	proj[2] = _projectionMtx[0][2];
	proj[3] = _projectionMtx[0][3];
	proj[4] = _projectionMtx[1][0];
	proj[5] = _projectionMtx[1][1];
	proj[6] = _projectionMtx[1][2];
	proj[7] = _projectionMtx[1][3];
	proj[8] = _projectionMtx[2][0];
	proj[9] = _projectionMtx[2][1];
	proj[10] = _projectionMtx[2][2];
	proj[11] = _projectionMtx[2][3];
	proj[12] = _projectionMtx[3][0];
	proj[13] = _projectionMtx[3][1];
	proj[14] = _projectionMtx[3][2];
	proj[15] = _projectionMtx[3][3];

	/**
	 * View Matrix
	 *  11: 1 12: 0 13: 0 14: 0
		21: 0 22: 1 23: 0 24: 0
		31: 0 32: 0 33: 1 34: 0.1
		41: 0 42: 0 43: 0 44: 0
	 */

	 /**
		 _ObjTransformationMtx
		 11: -0.707107 	12: 0 			13: 0.707107 	14: -315.062
		 21: 0.122788 	22: 0.984808 	23: 0.122788 	24: -79.6138
		 31: -0.696364 	32: 0.173648 	33: -0.696364 	34: 40.7966
		 41: 0 			42: 0 			43: 0 			44: 0
	  */

	Mtx mv;
	guMtxConcat(_ObjTransformationMtx, _GRR_view, mv);

	Matrix4x4 matrix44(_ObjTransformationMtx);
	LOG("%s", matrix44.ToString().c_str());

	return;

	modl[0] = mv[0][0];
	modl[1] = mv[0][1];
	modl[2] = mv[0][2];
	modl[3] = mv[0][3];
	modl[4] = mv[1][0];
	modl[5] = mv[1][1];
	modl[6] = mv[1][2];
	modl[7] = mv[1][3];
	modl[8] = mv[2][0];
	modl[9] = mv[2][1];
	modl[10] = mv[2][2];
	modl[11] = mv[2][3];
	modl[12] = mv[3][0];
	modl[13] = mv[3][1];
	modl[14] = mv[3][2];
	modl[15] = mv[3][3];

	//glGetFloatv(2983, proj);
	//glGetFloatv(2982, modl);

	clip[0] = (modl[0] * proj[0] + modl[1] * proj[4] + modl[2] * proj[8] + modl[3] * proj[12]);
	clip[1] = (modl[0] * proj[1] + modl[1] * proj[5] + modl[2] * proj[9] + modl[3] * proj[13]);
	clip[2] = (modl[0] * proj[2] + modl[1] * proj[6] + modl[2] * proj[10] + modl[3] * proj[14]);
	clip[3] = (modl[0] * proj[3] + modl[1] * proj[7] + modl[2] * proj[11] + modl[3] * proj[15]);

	clip[4] = (modl[4] * proj[0] + modl[5] * proj[4] + modl[6] * proj[8] + modl[7] * proj[12]);
	clip[5] = (modl[4] * proj[1] + modl[5] * proj[5] + modl[6] * proj[9] + modl[7] * proj[13]);
	clip[6] = (modl[4] * proj[2] + modl[5] * proj[6] + modl[6] * proj[10] + modl[7] * proj[14]);
	clip[7] = (modl[4] * proj[3] + modl[5] * proj[7] + modl[6] * proj[11] + modl[7] * proj[15]);

	clip[8] = (modl[8] * proj[0] + modl[9] * proj[4] + modl[10] * proj[8] + modl[11] * proj[12]);
	clip[9] = (modl[8] * proj[1] + modl[9] * proj[5] + modl[10] * proj[9] + modl[11] * proj[13]);
	clip[10] = (modl[8] * proj[2] + modl[9] * proj[6] + modl[10] * proj[10] + modl[11] * proj[14]);
	clip[11] = (modl[8] * proj[3] + modl[9] * proj[7] + modl[10] * proj[11] + modl[11] * proj[15]);

	clip[12] = (modl[12] * proj[0] + modl[13] * proj[4] + modl[14] * proj[8] + modl[15] * proj[12]);
	clip[13] = (modl[12] * proj[1] + modl[13] * proj[5] + modl[14] * proj[9] + modl[15] * proj[13]);
	clip[14] = (modl[12] * proj[2] + modl[13] * proj[6] + modl[14] * proj[10] + modl[15] * proj[14]);
	clip[15] = (modl[12] * proj[3] + modl[13] * proj[7] + modl[14] * proj[11] + modl[15] * proj[15]);

	m_Frustum[0][0] = (clip[3] - clip[0]);
	m_Frustum[0][1] = (clip[7] - clip[4]);
	m_Frustum[0][2] = (clip[11] - clip[8]);
	m_Frustum[0][3] = (clip[15] - clip[12]);

	NormalizePlane(m_Frustum, 0);

	m_Frustum[1][0] = (clip[3] + clip[0]);
	m_Frustum[1][1] = (clip[7] + clip[4]);
	m_Frustum[1][2] = (clip[11] + clip[8]);
	m_Frustum[1][3] = (clip[15] + clip[12]);

	NormalizePlane(m_Frustum, 1);

	m_Frustum[2][0] = (clip[3] + clip[1]);
	m_Frustum[2][1] = (clip[7] + clip[5]);
	m_Frustum[2][2] = (clip[11] + clip[9]);
	m_Frustum[2][3] = (clip[15] + clip[13]);

	NormalizePlane(m_Frustum, 2);

	m_Frustum[3][0] = (clip[3] - clip[1]);
	m_Frustum[3][1] = (clip[7] - clip[5]);
	m_Frustum[3][2] = (clip[11] - clip[9]);
	m_Frustum[3][3] = (clip[15] - clip[13]);

	NormalizePlane(m_Frustum, 3);

	m_Frustum[4][0] = (clip[3] - clip[2]);
	m_Frustum[4][1] = (clip[7] - clip[6]);
	m_Frustum[4][2] = (clip[11] - clip[10]);
	m_Frustum[4][3] = (clip[15] - clip[14]);

	NormalizePlane(m_Frustum, 4);

	m_Frustum[5][0] = (clip[3] + clip[2]);
	m_Frustum[5][1] = (clip[7] + clip[6]);
	m_Frustum[5][2] = (clip[11] + clip[10]);
	m_Frustum[5][3] = (clip[15] + clip[14]);

	NormalizePlane(m_Frustum, 5);
}

void Frustrum::NormalizePlane(float frustum[6][4], int side)
{
	float magnitude = (float)sqrt(frustum[side][0] * frustum[side][0] + frustum[side][1] * frustum[side][1] + frustum[side][2] * frustum[side][2]);

	frustum[side][0] /= magnitude;
	frustum[side][1] /= magnitude;
	frustum[side][2] /= magnitude;
	frustum[side][3] /= magnitude;
}

Frustrum& Frustrum::Instance()
{
	static Frustrum frustum;
	frustum.CalculateFrustum();
	return frustum;
}

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

#ifndef _BLOCKRENDERHELPER_H_
#define _BLOCKRENDERHELPER_H_

#include <stddef.h>
#include "../utils/MathHelper.h"

typedef struct BlockFaceVisibiltyVO
{
	bool bLeftFace = false;
	bool bRightFace = false;
	bool bFrontFace = false;
	bool bBackFace = false;
	bool bTopFace = false;
	bool bBottomFace = false;
	unsigned int faces = 0;
} BlockFaceVisibiltyVO;

typedef struct BlockRenderVO
{
	BlockFaceVisibiltyVO* pFaceVO = NULL;
	Vector3f* pBlockPosition = NULL;
} BlockRenderVO;


#endif /* _BLOCKRENDERHELPER_H_ */

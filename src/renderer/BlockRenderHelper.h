
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

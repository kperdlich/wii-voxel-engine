
#ifndef SRC_GUI_WORLD_BLOCKS_BLOCKRENDERHELPER_H_
#define SRC_GUI_WORLD_BLOCKS_BLOCKRENDERHELPER_H_

#include <stddef.h>
#include "../../../utils/MathHelper.h"

typedef struct BlockFaceVisibiltyData
{
	bool bLeftFace = false;
	bool bRightFace = false;
	bool bFrontFace = false;
	bool bBackFace = false;
	bool bTopFace = false;
	bool bBottomFace = false;
	unsigned int faces = 0;
} BlockFaceVisibiltyData;

typedef struct BlockRenderData
{
	BlockFaceVisibiltyData* pFaceData = NULL;
	Vector3f* pBlockPosition = NULL;
} BlockRenderData;


#endif /* SRC_GUI_WORLD_BLOCKS_BLOCKRENDERHELPER_H_ */

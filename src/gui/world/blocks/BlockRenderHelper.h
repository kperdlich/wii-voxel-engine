
#ifndef SRC_GUI_WORLD_BLOCKS_BLOCKRENDERHELPER_H_
#define SRC_GUI_WORLD_BLOCKS_BLOCKRENDERHELPER_H_

#include <stddef.h>
#include "../../../utils/MathHelper.h"

typedef struct BlockFaceVisibiltyData
{
	bool LeftFace = false;
	bool RightFace = false;
	bool FrontFace = false;
	bool BackFace = false;
	bool TopFace = false;
	bool BottomFace = false;
	unsigned int Faces = 0;
} BlockFaceVisibiltyData;

typedef struct BlockRenderData
{
	BlockFaceVisibiltyData* FaceData = NULL;
	Vector3f* BlockPosition = NULL;
} BlockRenderData;


#endif /* SRC_GUI_WORLD_BLOCKS_BLOCKRENDERHELPER_H_ */

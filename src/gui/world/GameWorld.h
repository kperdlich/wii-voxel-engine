/*
 * GameWorld.h
 *
 *  Created on: 23.01.2016
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_GAMEWORLD_H_
#define SRC_GUI_WORLD_GAMEWORLD_H_

#include "../../gui/scenes/Basic3DScene.h"
#include "../../utils/MathHelper.h"
#include "blocks/BlockManager.h"
#include "blocks/BlockRenderer.h"

#include "chunk/Chunk.h"
#include <map>

#define CHUNK_AMOUNT_X 50
#define CHUNK_AMOUNT_Z 50

#define CHUNK_PLAYER_FOV 7 // how many chunks the player can see

typedef struct ChunkPositionComparer
{
	bool operator()(class Vector3f* s1, class Vector3f* s2) const
	{
	    return s1->GetX() < s2->GetX() || (s1->GetX() == s2->GetX() && s1->GetZ() < s2->GetZ());
	}
} ChunkPositionComparer;

class CGameWorld {
public:
	CGameWorld( class Basic3DScene* pScene );
	virtual ~CGameWorld();
	void GenerateWorld();
	void Draw();

	class CBlockManager& GetBlockManager();
	class CChunk* GetChunkAt(Vector3f& centerPosition);
	class CChunk* GetChunkByWorldPosition(Vector3f& worldPosition);
	void RemoveBlockByWorldPosition(Vector3f& blockPosition);
	void UpdateFocusedBlockByWorldPosition( Vector3f& blockPosition );


private:
	bool ChunkInFov( Vector3f& chunkPosition, Vector3f& playerPosition, unsigned int fov);
	void DrawFocusOnSelectedCube();

private:
	class Basic3DScene* m_pScene;
	CBlockManager* m_blockManager;
	std::map<class Vector3f*, class CChunk*, ChunkPositionComparer> m_ChunkList;

	Vector3f m_SelectedBlockPosition;
	bool m_bHasSelectedBlock = false;

	char* m_pChunkLogBuffer;
	char* m_pDisplayListSizeLogBuffer;

	char* m_pBlocksLogBuffer;
	char* m_pFaceLogBuffer;

};

#endif /* SRC_GUI_WORLD_GAMEWORLD_H_ */

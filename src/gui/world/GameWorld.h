/*
 * GameWorld.h
 *
 *  Created on: 23.01.2016
 *      Author: Kevin
 */

#ifndef SRC_GUI_WORLD_GAMEWORLD_H_
#define SRC_GUI_WORLD_GAMEWORLD_H_

#include "../../gui/scenes/Basic3DScene.h"
#include "blocks/BlockManager.h"
#include "blocks/BlockRenderer.h"

#define WORLD_X 20
#define WORLD_Y 1
#define WORLD_Z 20

class Basic3DScene;

class CGameWorld {
public:
	CGameWorld( Basic3DScene* pScene );
	virtual ~CGameWorld();
	void GenerateWorld();
	void Draw();

private:
	Basic3DScene* m_pScene;
	CBlockManager* m_blockManager;
	unsigned int m_worldMap[WORLD_X][WORLD_Y][WORLD_Z];

};

#endif /* SRC_GUI_WORLD_GAMEWORLD_H_ */

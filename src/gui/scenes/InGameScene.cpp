/*
 * InGameScene.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "InGameScene.h"
#include "../../utils/Debug.h"
#include "../world/hud/CHotbar.h"
#include "Hotbar_png.h"
#include "ItemCSS_png.h"
#include "../../entity/Block.h"
#include "../../entity/Player.h"


#define IGS_HUD_HOTBAR "IGS_HUD_HOTBAR"

InGameScene::InGameScene() { }

InGameScene::~InGameScene() { }

void InGameScene::update()
{
	Basic3DScene::update();
	Player* player = static_cast<Player*>(m_entityHandler->getPlayer());
	player->update();
}

void InGameScene::load()
{
	Basic3DScene::load();
	initEntities();
	drawMap();
	m_uiElements.push_back( new CHotbar( IGS_HUD_HOTBAR, m_TextureHandler->createTexture(Hotbar_png)) );
}

void InGameScene::draw() {
	Basic3DScene::draw();

	// debug stuff
	Player* player = static_cast<Player*>(m_entityHandler->getPlayer());

	char* playerPosition = new char[100];
	sprintf(playerPosition, "Player Position: x:%i, y:%i, z:%i", static_cast<int>(player->getWorldPosition().getX()), static_cast<int>(player->getWorldPosition().getY()), static_cast<int>(player->getWorldPosition().getZ()));
	Debug::getInstance().log( playerPosition );

	char* playerRotation = new char[100];
	sprintf(playerRotation, "Player Rotation: x:%i, y:%i, z:%i", static_cast<int>(player->getWorldAngle().getX()), static_cast<int>(player->getWorldAngle().getY()), static_cast<int>(player->getWorldAngle().getZ()));
	Debug::getInstance().log( playerRotation );

}

void InGameScene::initEntities()
{
	m_entityHandler->addEntity( new Player( m_mainCamera ) );
}


void InGameScene::drawMap()
{
	// just draw a basic 10*10 map
	float blockSize = 1.0f;
	float ypos = -3.0f;
	for ( unsigned int x = 0; x < 10; x++)
	{
		for ( unsigned int z = 0; z < 10; z++)
		{
			m_entityHandler->addEntity( new CBlock( Vector3f(x + (x * blockSize ), ypos, z + (z * blockSize )), blockSize) );
		}
	}

}

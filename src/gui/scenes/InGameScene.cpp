/*
 * InGameScene.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "InGameScene.h"
#include "../../utils/Debug.h"
#include "../world/hud/CHotbar.h"
#include "../components/Cursor.h"
#include "Hotbar_png.h"
#include "Crosshair_png.h"
#include "../../entity/Player.h"


#define IGS_HUD_HOTBAR "IGS_HUD_HOTBAR"
#define IGS_HUD_CROSSHAIR "IGS_HUD_CROSSHAIR"

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
	m_uiElements.push_back( new CHotbar( IGS_HUD_HOTBAR, m_TextureHandler->createTexture(Hotbar_png, IGS_HUD_HOTBAR)) );
	m_uiElements.push_back( new Cursor( IGS_HUD_CROSSHAIR, m_TextureHandler->createTexture(Crosshair_png, IGS_HUD_CROSSHAIR)) );

	m_pGameWorld = new CGameWorld(this);
	m_pGameWorld->GenerateWorld();

}

void InGameScene::draw()
{
	Basic3DScene::draw();

#ifdef DEBUG
	Player* player = static_cast<Player*>(m_entityHandler->getPlayer());

	char* playerPosition = new char[100];
	sprintf(playerPosition, "Player Position: x:%i, y:%i, z:%i", static_cast<int>(player->getPosition().getX()), static_cast<int>(player->getPosition().getY()), static_cast<int>(player->getPosition().getZ()));
	Debug::getInstance().log( playerPosition );

	char* playerRotation = new char[100];
	sprintf(playerRotation, "Player Rotation: x:%i, y:%i, z:%i", static_cast<int>(player->getRotation().getX()), static_cast<int>(player->getRotation().getY()), static_cast<int>(player->getRotation().getZ()));
	Debug::getInstance().log( playerRotation );
#endif

}

void InGameScene::initEntities()
{
	Player* pPlayer = new Player();
	pPlayer->setPosition(Vector3f(.0f, 2.0f, 10.0f));
	m_mainCamera->attachTo(*pPlayer);
	m_entityHandler->addEntity(pPlayer);
}

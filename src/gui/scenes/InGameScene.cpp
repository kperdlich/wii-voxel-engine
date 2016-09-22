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


static char* pPlayerPositionLogBuffer;
static char* pPlayerRotationLogBuffer;

InGameScene::InGameScene()
{
	#ifdef DEBUG
		pPlayerPositionLogBuffer = new char[100];
		pPlayerRotationLogBuffer = new char[100];
	#endif
}

InGameScene::~InGameScene()
{
	#ifdef DEBUG
		delete [] pPlayerPositionLogBuffer;
		delete [] pPlayerRotationLogBuffer;
	#endif
}

void InGameScene::update()
{
	Basic3DScene::update();
	Player* player = static_cast<Player*>(m_entityHandler->GetPlayer());
	player->update();
}

void InGameScene::load()
{
	Basic3DScene::load();

	m_uiElements.push_back( new CHotbar( IGS_HUD_HOTBAR, m_TextureHandler->createTexture(Hotbar_png, IGS_HUD_HOTBAR)) );
	m_uiElements.push_back( new Cursor( IGS_HUD_CROSSHAIR, m_TextureHandler->createTexture(Crosshair_png, IGS_HUD_CROSSHAIR)) );

	m_pGameWorld = new CGameWorld(this);
	m_pGameWorld->GenerateWorld();

	initEntities();
}

void InGameScene::draw()
{
	Basic3DScene::draw();

#ifdef DEBUG
	Player* player = static_cast<Player*>(m_entityHandler->GetPlayer());

	sprintf(pPlayerPositionLogBuffer, "Player Position: x:%i, y:%i, z:%i", static_cast<int>(player->GetPosition().GetX()), static_cast<int>(player->GetPosition().GetY()), static_cast<int>(player->GetPosition().GetZ()));
	Debug::getInstance().log( pPlayerPositionLogBuffer );

	sprintf(pPlayerRotationLogBuffer, "Player Rotation: x:%i, y:%i, z:%i", static_cast<int>(player->getRotation().GetX()), static_cast<int>(player->getRotation().GetY()), static_cast<int>(player->getRotation().GetZ()));
	Debug::getInstance().log( pPlayerRotationLogBuffer );
#endif

}

void InGameScene::initEntities()
{
	Player* pPlayer = new Player();
	pPlayer->SetPosition(Vector3f(.0f, CHUNK_SIZE_Y + 1.0f, 0.0f));
	pPlayer->setRotation(Vector3f(.0f, 225.0f, .0f));
	pPlayer->SetWorld(m_pGameWorld);
	m_mainCamera->attachTo(*pPlayer);
	m_entityHandler->addEntity(pPlayer);
}

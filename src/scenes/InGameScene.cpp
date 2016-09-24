/*
 * InGameScene.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "InGameScene.h"
#include "../utils/Debug.h"
#include "../world/hud/CHotbar.h"
#include "../components/Cursor.h"
#include "Hotbar_png.h"
#include "Crosshair_png.h"
#include "../entity/Player.h"

#define IGS_HUD_HOTBAR "IGS_HUD_HOTBAR"
#define IGS_HUD_CROSSHAIR "IGS_HUD_CROSSHAIR"

#ifdef DEBUG
	static char* pPlayerPositionLogBuffer;
	static char* pPlayerRotationLogBuffer;
#endif

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

void InGameScene::Update()
{
	Basic3DScene::Update();
	Player* player = static_cast<Player*>(m_entityHandler->GetPlayer());
	player->Update();
}

void InGameScene::Load()
{
	Basic3DScene::Load();

	m_uiElements.push_back( new CHotbar( IGS_HUD_HOTBAR, m_TextureHandler->CreateTexture(Hotbar_png, IGS_HUD_HOTBAR)) );
	m_uiElements.push_back( new Cursor( IGS_HUD_CROSSHAIR, m_TextureHandler->CreateTexture(Crosshair_png, IGS_HUD_CROSSHAIR)) );

	m_pGameWorld = new CGameWorld(this);
	m_pGameWorld->GenerateWorld();

	initEntities();
}

void InGameScene::Draw()
{
	Basic3DScene::Draw();

#ifdef DEBUG
	Player* player = static_cast<Player*>(m_entityHandler->GetPlayer());

	sprintf(pPlayerPositionLogBuffer, "Player Position: x:%i, y:%i, z:%i", static_cast<int>(player->GetPosition().GetX()), static_cast<int>(player->GetPosition().GetY()), static_cast<int>(player->GetPosition().GetZ()));
	Debug::GetInstance().Log( pPlayerPositionLogBuffer );

	sprintf(pPlayerRotationLogBuffer, "Player Rotation: x:%i, y:%i, z:%i", static_cast<int>(player->GetRotation().GetX()), static_cast<int>(player->GetRotation().GetY()), static_cast<int>(player->GetRotation().GetZ()));
	Debug::GetInstance().Log( pPlayerRotationLogBuffer );
#endif

}

void InGameScene::initEntities()
{
	Player* pPlayer = new Player();
	pPlayer->SetPosition(Vector3f(.0f, CHUNK_SIZE_Y + 1.0f, 0.0f));
	pPlayer->SetRotation(Vector3f(.0f, 225.0f, .0f));
	pPlayer->SetWorld(m_pGameWorld);
	m_mainCamera->AttachTo(*pPlayer);
	m_entityHandler->AddEntity(pPlayer);
}

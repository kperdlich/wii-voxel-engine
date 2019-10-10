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

#include "scenes/InGameScene.h"
#include "utils/Debug.h"
#include "world/hud/Hotbar.h"
#include "components/Cursor.h"
#include "components/worldloader.h"
#include "entity/Player.h"
#include "event/event.h"
#include "event/eventmanager.h"
#include "net/NetworkManager.h"
#include "net/packet/PacketHandshake.h"
#include "textures/Sprite.h"
#include "Hotbar_png.h"
#include "Crosshair_png.h"
#include "LoadingBackground_png.h"

#define IGS_HUD_HOTBAR "IGS_HUD_HOTBAR"
#define IGS_HUD_CROSSHAIR "IGS_HUD_CROSSHAIR"
#define IGS_LOADING_SCREEN "IGS_LOADING_SCREEN"

InGameScene::InGameScene() {}

InGameScene::~InGameScene() {}

void InGameScene::Update(float deltaSeconds)
{
	Basic3DScene::Update(deltaSeconds);

	if (m_bLoaded)
	{
		CPlayer* player = static_cast<CPlayer*>(m_entityHandler->GetPlayer());
		player->Update(deltaSeconds);
	}
}

void InGameScene::Load()
{
	m_pGameWorld = new GameWorld();
	InitEntities();
	m_pGameWorld->GenerateWorld();

	EventManager::AddListener(this, EVENT_PREPARE_WORLD);
	m_pWorldLoader = new WorldLoader(IGS_LOADING_SCREEN,
		Sprite::Create(LoadingBackground_png, LoadingBackground_png_size, IGS_LOADING_SCREEN, 0));
	m_uiElements.push_back(m_pWorldLoader);
}

void InGameScene::Unload()
{
	delete m_pGameWorld;
	Basic3DScene::Unload();
}


void InGameScene::Draw()
{
	if (m_bLoaded)
		Basic3DScene::Draw();
	else
		Basic3DScene::Render2D();
}

void InGameScene::OnEvent(Event event)
{
	switch (event.ID)
	{
	case EVENT_PREPARE_WORLD:
	{
		EventManager::RemoveListener(this, EVENT_PREPARE_WORLD);
		m_pWorldLoader = nullptr;
		m_spriteStageManager->Clear();
		ClearUiElements();
		m_uiElements.push_back(new Hotbar(IGS_HUD_HOTBAR, Sprite::Create(Hotbar_png, Hotbar_png_size, IGS_HUD_HOTBAR)));
		m_uiElements.push_back(new Cursor(IGS_HUD_CROSSHAIR, Sprite::Create(Crosshair_png, Crosshair_png_size, IGS_HUD_CROSSHAIR)));
		Basic3DScene::Load();
		break;
	}
	default:
		break;
	}
}

void InGameScene::InitEntities()
{
	CPlayer* pPlayer = new CPlayer();
	pPlayer->SetPosition(Vector3(-189.5, 74.5, 248.5));
	pPlayer->SetRotation(Vector3(10.0f, 225.0f, .0f));
	pPlayer->SetWorld(m_pGameWorld);
	m_mainCamera->AttachTo(*pPlayer);
	m_mainCamera->SetCameraOffset(1.32f);
	m_entityHandler->AddEntity(pPlayer);
}

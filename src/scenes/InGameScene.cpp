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

#include "InGameScene.h"
#include "../utils/Debug.h"
#include "../world/hud/Hotbar.h"
#include "../components/Cursor.h"
#include "Hotbar_png.h"
#include "Crosshair_png.h"
#include "../entity/Player.h"
#include "../net/NetworkManager.h"
#include "../net/packet/PacketHandshake.h"

#define IGS_HUD_HOTBAR "IGS_HUD_HOTBAR"
#define IGS_HUD_CROSSHAIR "IGS_HUD_CROSSHAIR"


InGameScene::InGameScene() {}

InGameScene::~InGameScene() {}

void InGameScene::Update(float deltaSeconds)
{
    Basic3DScene::Update(deltaSeconds);
    CPlayer* player = static_cast<CPlayer*>(m_entityHandler->GetPlayer());
    player->Update(deltaSeconds);
}

void InGameScene::Load()
{
    m_uiElements.push_back( new Hotbar( IGS_HUD_HOTBAR, Sprite::Create(Hotbar_png, Hotbar_png_size, IGS_HUD_HOTBAR)) );
    m_uiElements.push_back( new Cursor( IGS_HUD_CROSSHAIR, Sprite::Create(Crosshair_png, Crosshair_png_size, IGS_HUD_CROSSHAIR)) );

    m_pGameWorld = new GameWorld();
    InitEntities();
    m_pGameWorld->GenerateWorld();

    // todo move to multiplayer scene
    NetworkManager::Get().Connect("192.168.178.27", 25565);
    PacketHandshake hs("DaeFennek", "192.168.178.27", 25565);
    hs.Send();

    Basic3DScene::Load();
}

void InGameScene::Unload()
{
    delete m_pGameWorld;
    Basic3DScene::Unload();
}


void InGameScene::Draw()
{
    Basic3DScene::Draw();   

#ifdef DEBUG
    /*
    GRRLIB_SetLightAmbient(0x404040FF);
    GRRLIB_SetLightSpot(0, (guVector){ 10.0f, 0.0f, 10.0f }, (guVector){  0.0f, 0.0f, 0.0f }, 1.0f, 3.0f, 1.0f, 1.0f, 0.0f, 0.0f, GRRLIB_RED);

    f32 lightx=-0.96f;
    f32 lighty=-0.48f;
    f32 lightz=-2.6f;

    f32 a = -0.253f;
    f32 b = 0.133f;
    f32 c = 1.452f;
    f32 d = 0.7080f;
    f32 e = 0.0f;
    f32 f = 0.0f;

   GRRLIB_SetLightAmbient(0x404040FF);
   GRRLIB_SetLightSpot(1, (guVector){2, 0.8, 5.0 }, (guVector){lightx,lighty,lightz}, a, b, c, d, e, f, 0xFFFF00FF);
   GRRLIB_SetLightDiff(0,(guVector){5.0f,5.0f,5.0f},10.0f,0.1f,0xFFFFFFFF);*/

#endif
}

void InGameScene::InitEntities()
{
    CPlayer* pPlayer = new CPlayer();
    pPlayer->SetPosition(Vector3(10.0f, CHUNK_BLOCK_SIZE_Y, 10.0f));
    pPlayer->SetRotation(Vector3(10.0f, 225.0f, .0f));
	pPlayer->SetWorld(m_pGameWorld);
	m_mainCamera->AttachTo(*pPlayer);
	m_entityHandler->AddEntity(pPlayer);
}

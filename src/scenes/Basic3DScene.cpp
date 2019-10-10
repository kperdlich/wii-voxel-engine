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

#include "scenes/Basic3DScene.h"
#include "renderer/MasterRenderer.h"
#include "utils/Debug.h"

constexpr float MIN_DIST = 0.1f;
constexpr float MAX_DIST = 200.0f;
constexpr float FIELD_OF_VIEW = 70.0f;

Basic3DScene::Basic3DScene()
{
	m_entityHandler = new EntityHandler();
	m_mainCamera = new Camera();
	m_skyBox = new SkyBox();
}

Basic3DScene::~Basic3DScene()
{
	delete m_entityHandler;
	delete m_mainCamera;
	delete m_skyBox;
}

void Basic3DScene::Load()
{
	m_mainCamera->Init();
	m_skyBox->Init();
	Scene::Load();
}

void Basic3DScene::Draw()
{
	//GRRLIB_SetLightSpot(0, (guVector){ 10.0f, 0.0f, 10.0f }, (guVector){  0.0f, 0.0f, 0.0f }, -3.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0x0000FFFF);
	//GRRLIB_SetLightDiff(0, (guVector){ 10.0f, 10.0f, 10.0f }, 10.0f,1.0f,0xFFFFFFFF);

	GRRLIB_3dMode(MIN_DIST, MAX_DIST, FIELD_OF_VIEW, 1, 1);

	GRRLIB_ObjectViewBegin();
	GRRLIB_ObjectViewScale(m_mainCamera->GetWorldScaleX(), m_mainCamera->GetWorldScaleY(), m_mainCamera->GetWorldScaleZ());
	GRRLIB_ObjectViewTrans(-50, -50, -50);
	GRRLIB_ObjectViewRotate(0, 360 - m_mainCamera->GetWorldAngleY(), 0);
	GRRLIB_ObjectViewRotate(m_mainCamera->GetWorldAngleX(), 0, 0);
	GRRLIB_ObjectViewRotate(0, 0, m_mainCamera->GetWorldAngleZ());
	GRRLIB_ObjectViewEnd();

	MasterRenderer::SetGraphicsMode(true, false);
	MasterRenderer::EnableFog();
	m_skyBox->Render();
	MasterRenderer::SetGraphicsMode(true, true);

	GRRLIB_ObjectViewBegin();
	GRRLIB_ObjectViewScale(m_mainCamera->GetWorldScaleX(), m_mainCamera->GetWorldScaleY(), m_mainCamera->GetWorldScaleZ());
	GRRLIB_ObjectViewTrans(-m_mainCamera->GetWorldPositionX(), -m_mainCamera->GetWorldPositionY(), -m_mainCamera->GetWorldPositionZ());
	GRRLIB_ObjectViewRotate(0, 360 - m_mainCamera->GetWorldAngleY(), 0);
	GRRLIB_ObjectViewRotate(m_mainCamera->GetWorldAngleX(), 0, 0);
	GRRLIB_ObjectViewRotate(0, 0, m_mainCamera->GetWorldAngleZ());
	GRRLIB_ObjectViewEnd();

	m_pGameWorld->Draw();

	Render2D();
}

void Basic3DScene::Render2D() const
{
	GRRLIB_2dMode();

	auto sprites = m_spriteStageManager->GetSpriteRenderList();
	for (auto it = sprites.begin(); it != sprites.end(); it++)
	{
		(*it)->Render();
	}
}

void Basic3DScene::Update(float deltaSeconds)
{
	for (uint32_t i = 0; i < m_uiElements.size(); i++)
	{
		m_uiElements[i]->Update();
	}
}

EntityHandler& Basic3DScene::GetEntityHandler()
{
	return *m_entityHandler;
}

void Basic3DScene::ClearUiElements()
{
	for (uint32_t i = 0; i < m_uiElements.size(); i++)
	{
		delete m_uiElements[i];
	}

	m_uiElements.clear();
}

void Basic3DScene::Unload()
{
	ClearUiElements();
	m_entityHandler->Clear();
	m_skyBox->Clear();
	Scene::Unload();
}

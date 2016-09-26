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

#include "Basic3DScene.h"
#include "../utils/Debug.h"

#define MIN_DIST 0.1f
#define MAX_DIST 200.0f
#define FIELD_OF_VIEW 90.0f

Basic3DScene::Basic3DScene()
{
	m_Renderer = new Renderer3D();
	m_entityHandler = new EntityHandler();
	m_mainCamera = new Camera();
}

Basic3DScene::~Basic3DScene()
{
	delete m_pGameWorld;
	delete m_entityHandler;
	delete m_mainCamera;
}

void Basic3DScene::Load()
{
	BasicScene::Load();
	m_mainCamera->Init();
}

void Basic3DScene::Draw()
{
	//GRRLIB_SetLightSpot(0, (guVector){ 10.0f, 0.0f, 10.0f }, (guVector){  0.0f, 0.0f, 0.0f }, -3.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0x0000FFFF);
	//GRRLIB_SetLightDiff(0, (guVector){ 10.0f, 10.0f, 10.0f }, 10.0f,1.0f,0xFFFFFFFF);

	GRRLIB_3dMode(MIN_DIST, MAX_DIST, FIELD_OF_VIEW, 1, 1);

	GRRLIB_ObjectViewBegin();
	GRRLIB_ObjectViewScale( m_mainCamera->GetWorldScaleX(), m_mainCamera->GetWorldScaleY(), m_mainCamera->GetWorldScaleZ() );
	GRRLIB_ObjectViewTrans( -m_mainCamera->GetWorldPositionX(), -m_mainCamera->GetWorldPositionY(), -m_mainCamera->GetWorldPositionZ() );
	GRRLIB_ObjectViewRotate( 0, 360 - m_mainCamera->GetWorldAngleY(), 0);
	GRRLIB_ObjectViewRotate( m_mainCamera->GetWorldAngleX(), 0, 0);
	GRRLIB_ObjectViewRotate( 0, 0, m_mainCamera->GetWorldAngleZ());
	GRRLIB_ObjectViewEnd();

	m_pGameWorld->Draw();

	for (auto it = m_entityHandler->GetEntities()->begin(); it != m_entityHandler->GetEntities()->end(); ++it)
	{
		if (it->second->IsVisible())
		{
			Get3DRenderer().drawEntity( it->second );
		}
	}

	GRRLIB_2dMode();

	auto textures = m_TextureHandler->GetTextures();
	for ( auto it = textures->begin(); it != textures->end(); it++)
	{
		if ((*it)->IsVisible())
		{
			Get3DRenderer().draw2DTexture( (*it) );
		}
	}
}

void Basic3DScene::Update()
{
	for (unsigned int i = 0; i < m_uiElements.size(); i++)
	{
		m_uiElements[i]->Update();
	}
}

Renderer3D& Basic3DScene::Get3DRenderer()
{
	return static_cast<Renderer3D&>(*m_Renderer);
}

EntityHandler& Basic3DScene::GetEntityHandler()
{
	return *m_entityHandler;
}

void Basic3DScene::Unload() {
	for (uint i = 0; i < m_uiElements.size(); i++)
	{
		delete m_uiElements[i];
	}

	m_uiElements.clear();
	m_entityHandler->Clear();
	BasicScene::Unload();
}

void Basic3DScene::SetGraphicsMode(bool textureMode, bool normalMode)
{
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	if(normalMode)
		GX_SetVtxDesc(GX_VA_NRM, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	if(textureMode)
		GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	if(normalMode)
		GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	if(textureMode)
		GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

	if(textureMode)
		GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
	else
		GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}

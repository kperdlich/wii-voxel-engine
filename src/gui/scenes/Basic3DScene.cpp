/*
 * Basic3DScene.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "Basic3DScene.h"
#include "../../utils/Debug.h"

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

void Basic3DScene::load()
{
	BasicScene::load();
	m_mainCamera->init();
}

void Basic3DScene::draw()
{
	//GRRLIB_SetLightSpot(0, (guVector){ 10.0f, 0.0f, 10.0f }, (guVector){  0.0f, 0.0f, 0.0f }, -3.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0x0000FFFF);
	//GRRLIB_SetLightDiff(0, (guVector){ 10.0f, 10.0f, 10.0f }, 10.0f,1.0f,0xFFFFFFFF);

	GRRLIB_3dMode(MIN_DIST, MAX_DIST, FIELD_OF_VIEW, 1, 1);

	GRRLIB_ObjectViewBegin();
	GRRLIB_ObjectViewScale( m_mainCamera->getWorldScaleX(), m_mainCamera->getWorldScaleY(), m_mainCamera->getWorldScaleZ() );
	GRRLIB_ObjectViewTrans( -m_mainCamera->getWorldPositionX(), -m_mainCamera->getWorldPositionY(), -m_mainCamera->getWorldPositionZ() );
	GRRLIB_ObjectViewRotate( 0, 360 - m_mainCamera->getWorldAngleY(), 0);
	GRRLIB_ObjectViewRotate( m_mainCamera->getWorldAngleX(), 0, 0);
	GRRLIB_ObjectViewRotate( 0, 0, m_mainCamera->getWorldAngleZ());
	GRRLIB_ObjectViewEnd();

	m_pGameWorld->Draw();

	for (auto it = m_entityHandler->getEntities()->begin(); it != m_entityHandler->getEntities()->end(); ++it)
	{
		if (it->second->IsVisible())
		{
			getRenderer()->drawEntity( it->second );
		}
	}

	GRRLIB_2dMode();

	auto textures = m_TextureHandler->getTextures();
	for ( auto it = textures->begin(); it != textures->end(); it++)
	{
		if ((*it)->isVisible())
		{
			getRenderer()->draw2DTexture( (*it) );
		}
	}
}

void Basic3DScene::update()
{
	for (unsigned int i = 0; i < m_uiElements.size(); i++)
	{
		m_uiElements[i]->update();
	}
}

Renderer3D* Basic3DScene::getRenderer() {
	return static_cast<Renderer3D*>(m_Renderer);
}

EntityHandler& Basic3DScene::GetEntityHandler()
{
	return *m_entityHandler;
}

void Basic3DScene::unload() {
	for (uint i = 0; i < m_uiElements.size(); i++)
	{
		delete m_uiElements[i];
	}

	m_uiElements.clear();
	m_entityHandler->clear();
	BasicScene::unload();
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

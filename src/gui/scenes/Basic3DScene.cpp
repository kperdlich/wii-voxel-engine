/*
 * Basic3DScene.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "Basic3DScene.h"
#include "../../utils/Debug.h"

float a = 0;

Basic3DScene::Basic3DScene()
{
	m_Renderer = new Renderer3D();
	m_entityHandler = new EntityHandler();
	m_mainCamera = new Camera();
}

Basic3DScene::~Basic3DScene()
{
	delete m_entityHandler;
	delete m_mainCamera;
}

void Basic3DScene::load()
{
	m_mainCamera->init();
}

void Basic3DScene::draw()
{
	GRRLIB_3dMode(MIN_DIST, MAX_DIST, FIELD_OF_VIEW, 0, 0 );

	//GRRLIB_SetLightAmbient(0x333333FF);
	//GRRLIB_SetLightDiff(0,(guVector){1.0f,1.0f,1.0f},20.0f,0.8f,0xFF0000FF);

	GRRLIB_ObjectViewInv( -m_mainCamera->getWorldPositionX(), m_mainCamera->getWorldPositionY(), -m_mainCamera->getWorldPositionZ(),
			m_mainCamera->getWorldAngleX(), 360 - m_mainCamera->getWorldAngleY(), m_mainCamera->getWorldAngleZ(),
			m_mainCamera->getWorldScaleX(), m_mainCamera->getWorldScaleY(), m_mainCamera->getWorldScaleZ() );

	for (std::map<unsigned int, Entity*>::iterator it = m_entityHandler->getEntities()->begin(); it != m_entityHandler->getEntities()->end(); ++it)
	{
		if (it->second->isVisible())
		{
			getRenderer()->drawEntity( it->second );
		}
	}

	GRRLIB_2dMode();

	std::vector<BasicTexture*>* textures = m_TextureHandler->getTextures();
	for (uint i = 0; i < textures->size(); i++)
	{
		if (((*textures)[i])->isVisible())
		{
			getRenderer()->draw2DTexture( ((*textures)[i]) );
		}
	}
}

void Basic3DScene::update()
{
	for (int i = 0; i < m_uiElements.size(); i++)
	{
		static_cast<UIElement*>(m_uiElements[i])->update();
	}
}

Renderer3D* Basic3DScene::getRenderer() {
	return static_cast<Renderer3D*>(m_Renderer);
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

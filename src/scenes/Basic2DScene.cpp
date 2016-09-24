/*
 * Basic2DScene.cpp
 *
 *  Created on: 13.06.2015
 *      Author: Kevin
 */

#include "Basic2DScene.h"

Basic2DScene::Basic2DScene()
{
	m_Renderer = new Renderer2D();
}

Basic2DScene::~Basic2DScene() {
}

void Basic2DScene::Draw() {

	auto textures = m_TextureHandler->GetTextures();
	for (auto it = textures->begin(); it != textures->end(); it++)
	{
		if ((*it)->IsVisible())
		{
			Get2DRenderer().DrawTexture( (**it) );
		}
	}
}

void Basic2DScene::Load() {
	BasicScene::Load();
	GRRLIB_2dMode();
}


void Basic2DScene::Unload()
{
	for (uint i = 0; i < m_elements.size(); i++)
	{
		delete m_elements[i];
	}
	m_elements.clear();
	BasicScene::Unload();

}
Renderer2D& Basic2DScene::Get2DRenderer()
{
	return static_cast<Renderer2D&>(*m_Renderer);
}

void Basic2DScene::Update() {
	for (unsigned int i = 0; i < m_elements.size(); i++)
	{
		m_elements[i]->Update();
	}
}

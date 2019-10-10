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

#include "scenes/Basic2DScene.h"

Basic2DScene::Basic2DScene() {}

Basic2DScene::~Basic2DScene() {}

void Basic2DScene::Draw()
{
	auto sprites = m_spriteStageManager->GetSpriteRenderList();
	for (auto it = sprites.begin(); it != sprites.end(); it++)
	{
		(*it)->Render();
	}
}

void Basic2DScene::Load()
{
	Scene::Load();
	GRRLIB_2dMode();
}


void Basic2DScene::Unload()
{
	for (uint32_t i = 0; i < m_elements.size(); i++)
	{
		delete m_elements[i];
	}
	m_elements.clear();
	Scene::Unload();
}


void Basic2DScene::Update(float deltaSeconds)
{
	for (uint32_t i = 0; i < m_elements.size(); i++)
	{
		m_elements[i]->Update();
	}
}

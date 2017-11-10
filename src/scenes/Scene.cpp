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

#include "Scene.h"


Scene::Scene()
{
    m_TextureHandler = new SpriteStageManager();
}


Scene::~Scene()
{
	delete m_TextureHandler;
	delete m_Renderer;
}

void Scene::Load() {
}

void Scene::Unload()
{
    m_TextureHandler->DestroyAll();
}

void Scene::Draw() {
}

void Scene::Update(float deltaSeconds) {}

SpriteStageManager& Scene::GetTextureHandler() const
{
	return *m_TextureHandler;
}

Renderer& Scene::GetRenderer() const
{
	return *m_Renderer;
}

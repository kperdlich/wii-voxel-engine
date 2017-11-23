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
    m_spriteStageManager = new SpriteStageManager();
}


Scene::~Scene()
{
    if (m_spriteStageManager)
    {
        delete m_spriteStageManager;
        m_spriteStageManager = nullptr;
    }
}

void Scene::Load()
{
    m_bLoaded = true;
}

void Scene::Unload()
{
    m_spriteStageManager->Clear();
    m_bLoaded = false;
}

void Scene::Draw() {
}

void Scene::Update(float deltaSeconds) {}

SpriteStageManager& Scene::GetSpriteStageManager() const
{
    return *m_spriteStageManager;
}

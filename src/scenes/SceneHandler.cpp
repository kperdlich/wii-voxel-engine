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


#include "scenes/SceneHandler.h"
#include "scenes/IntroScene.h"
#include "scenes/MainMenuScene.h"
#include "scenes/InGameScene.h"
#include "utils/Debug.h"

SceneHandler::SceneHandler() {}

/**
 * delete all scenes
 */
SceneHandler::~SceneHandler()
{
    LOG("Try destroy SceneHandler");
    for ( uint32_t i = 0; i < m_scenes.size(); i++ )
	{       
        if ( m_scenes[i]->IsLoaded() )
        {
            m_scenes[i]->Unload();
        }
        delete m_scenes[i];
	}
    m_scenes.clear();
    LOG("SceneHandler destroyed");
}


void SceneHandler::Init() {

	/**
	 * Define all game scenes
	 * 1. Intro
	 * 2. Main menue
	 * 3. Ingame
	 */
    m_scenes.push_back( new IntroScene() );
    m_scenes.push_back( new MainMenuScene() );
    m_scenes.push_back( new InGameScene() );
	// ..

    LOG("SceneHandler initialized");
}

void SceneHandler::LoadScene( int32_t index )
{
    if ( index != m_currentSceneIndex && index != m_nextSceneIndex && index > INVALID_SCENE)
	{
		m_bLoadNextScene = true;
        m_nextSceneIndex = index;
	}
}


void SceneHandler::DrawScene()
{
    GetCurrentScene()->Draw();
}

void SceneHandler::Update(float deltaSeconds)
{
	if ( m_bLoadNextScene )
	{
		m_bLoadNextScene = false;

        if ( m_nextSceneIndex < ((int32_t)m_scenes.size()) && m_nextSceneIndex >= 0)
		{
            if ( m_currentSceneIndex > INVALID_SCENE )
			{
                LOG("Try unload Scene: %d", m_currentSceneIndex);
                GetCurrentScene()->Unload();
                LOG("Unloaded Scene: %d", m_currentSceneIndex);
			}
            m_currentSceneIndex = m_nextSceneIndex;
            LOG("Try loading Scene: %d", m_currentSceneIndex);
            GetCurrentScene()->Load();
            LOG("Loaded Scene: %d", m_currentSceneIndex);
		}
	}

    GetCurrentScene()->Update(deltaSeconds);
}

Scene* SceneHandler::GetCurrentScene()
{
    return m_scenes[m_currentSceneIndex];
}

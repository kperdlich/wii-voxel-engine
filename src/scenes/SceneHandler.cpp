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


#include "SceneHandler.h"
#include "../scenes/IntroScene.h"
#include "../scenes/MainMenuScene.h"
#include "../scenes/InGameScene.h"
#include "../utils/Debug.h"

SceneHandler::SceneHandler() {}

/**
 * delete all scenes
 */
SceneHandler::~SceneHandler() {
	for ( uint i = 0; i < m_Scenes.size(); i++ )
	{
		m_Scenes[i]->Unload();
		delete m_Scenes[i];
	}

	m_Scenes.clear();
}


void SceneHandler::Init() {

	/**
	 * Define all game scenes
	 * 1. Intro
	 * 2. Main menue
	 * 3. Ingame
	 */
	m_Scenes.push_back( new IntroScene() );
	m_Scenes.push_back( new MainMenuScene() );
	m_Scenes.push_back( new InGameScene() );
	// ..
}

void SceneHandler::LoadScene( int index )
{
	if ( index != m_currentSceneIndex && index != m_nextSceneIndex && index > INVALID_SCENE)
	{
		m_bLoadNextScene = true;
		m_nextSceneIndex = index;
	}
}


void SceneHandler::DrawScene()
{
	GetCurrentScene().Draw();
}

void SceneHandler::Update() {

	if ( m_bLoadNextScene )
	{
		m_bLoadNextScene = false;

		if ( m_nextSceneIndex < m_Scenes.size() && m_nextSceneIndex >= 0)
		{
			if ( m_currentSceneIndex > INVALID_SCENE )
			{
				GetCurrentScene().Unload();
			}
			m_currentSceneIndex = m_nextSceneIndex;
			GetCurrentScene().Load();
		}
	}

	GetCurrentScene().Update();
}

Scene& SceneHandler::GetCurrentScene()
{
	return *m_Scenes[m_currentSceneIndex];
}

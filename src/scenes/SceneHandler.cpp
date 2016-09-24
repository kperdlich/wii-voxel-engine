
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

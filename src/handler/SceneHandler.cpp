
#include "SceneHandler.h"
#include "../gui/scenes/IntroScene.h"
#include "../gui/scenes/MainMenuScene.h"
#include "../gui/scenes/InGameScene.h"
#include "../utils/Debug.h"

SceneHandler::SceneHandler() {
	m_currentSceneIndex = 0; // first will be 0
}

/**
 * delete all scenes
 */
SceneHandler::~SceneHandler() {
	for ( uint i = 0; i < m_Scenes.size(); i++ )
	{
		m_Scenes[i]->unload();
		delete m_Scenes[i];
	}

	m_Scenes.clear();
}


void SceneHandler::init() {

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

void SceneHandler::loadScene( uint index )
{
	m_bLoadNextScene = true;
	m_nextSceneIndex = index;
}


void SceneHandler::drawScene() {
	getCurrentScene()->draw();
}

void SceneHandler::update() {

	if ( m_bLoadNextScene )
	{
		m_bLoadNextScene = false;

		if ( m_nextSceneIndex < m_Scenes.size() && m_nextSceneIndex >= 0)
		{
			getCurrentScene()->unload();
			m_currentSceneIndex = m_nextSceneIndex;
			getCurrentScene()->load();
		}
	}

	getCurrentScene()->update();
}

Scene* SceneHandler::getCurrentScene() {
	return m_Scenes[m_currentSceneIndex];
}


#include "SceneHandler.h"
#include "../utils/Debug.h"

SceneHandler::SceneHandler() {
	m_CurrentSceneIndex = 0; // first will be 0
}

/**
 * delete all scenes
 */
SceneHandler::~SceneHandler() {
	for ( uint i = 0; i < m_Scenes.size(); i++ )
	{
		static_cast<Scene*>(m_Scenes[i])->unload();
		delete m_Scenes[i];
	}
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

	//LoadScene( 0, true ); // load first scene

}

void SceneHandler::loadScene( uint index ) {
	if ( index >= m_Scenes.size() )
		return;

	static_cast<Scene*>(m_Scenes[m_CurrentSceneIndex])->unload();
	m_CurrentSceneIndex = index;
	static_cast<Scene*>(m_Scenes[m_CurrentSceneIndex])->load();
}

void SceneHandler::drawScene() {
	static_cast<Scene*>(m_Scenes[m_CurrentSceneIndex])->draw();
}

void SceneHandler::update() {
	static_cast<Scene*>(m_Scenes[m_CurrentSceneIndex])->update();
}

Scene* SceneHandler::getCurrentScene() {
	return m_Scenes[m_CurrentSceneIndex];
}

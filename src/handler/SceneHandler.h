/*
 * SceneHandler.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef SRC_HANDLER_SCENEHANDLER_H_
#define SRC_HANDLER_SCENEHANDLER_H_

#include <vector>
#include "../gui/scenes/Scene.h"

#define INTRO_SCENE_ID 0
#define MAIN_MENU_ID 1
#define IN_GAME_ID 2

class SceneHandler
{

private:
	std::vector<Scene*> m_Scenes;
	uint m_currentSceneIndex;
	bool m_bLoadNextScene;
	uint m_nextSceneIndex;

public:
	SceneHandler();
	~SceneHandler();
	void init();
	void loadScene(uint index );
	void loadNextScene();
	void drawScene();
	void update();
	Scene* getCurrentScene();

};




#endif /* SRC_HANDLER_SCENEHANDLER_H_ */

/*
 * SceneHandler.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef _SCENEHANDLER_H_
#define _SCENEHANDLER_H_

#include <vector>
#include "../scenes/Scene.h"

#define INVALID_SCENE -1
#define INTRO_SCENE_ID 0
#define MAIN_MENU_ID 1
#define IN_GAME_ID 2

class SceneHandler
{

private:
	std::vector<Scene*> m_Scenes;
	int m_currentSceneIndex = INVALID_SCENE;
	bool m_bLoadNextScene = false;
	int m_nextSceneIndex = INVALID_SCENE;

public:
	SceneHandler();
	~SceneHandler();
	void Init();
	void LoadScene(int index );
	void LoadNextScene();
	void DrawScene();
	void Update();
	Scene& GetCurrentScene();

};


#endif /* _SCENEHANDLER_H_ */

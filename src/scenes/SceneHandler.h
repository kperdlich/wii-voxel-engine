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

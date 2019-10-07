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

#pragma once

#include <vector>
#include "scenes/Scene.h"

constexpr int32_t INVALID_SCENE     = -1;
constexpr int32_t INTRO_SCENE_ID    = 0;
constexpr int32_t MAIN_MENU_ID      = 1;
constexpr int32_t IN_GAME_ID        = 2;

class SceneHandler
{

private:
    std::vector<Scene*> m_scenes;
    int32_t m_currentSceneIndex = INVALID_SCENE;
	bool m_bLoadNextScene = false;
    int32_t m_nextSceneIndex = INVALID_SCENE;

public:
    SceneHandler();
    ~SceneHandler();    
    SceneHandler(const SceneHandler&) = delete;
    SceneHandler(SceneHandler&&) = delete;
    void operator=(const SceneHandler&) = delete;
    void operator=(SceneHandler&&) = delete;
	void Init();
    void LoadScene(int32_t index );
	void DrawScene();
    void Update(float deltaSeconds);
    Scene *GetCurrentScene();

};

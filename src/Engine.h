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

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "utils/GameHelper.h"
#include "utils/ColorHelper.h"
#include "commands/client/SwitchToIntroCommand.h"
#include "commands/client/SwitchToMainMenuCommand.h"

#include "input/InputHandler.h"
#include "scenes/SceneHandler.h"
#include "font/FontHandler.h"
#include "commands/BasicCommandHandler.h"

#define DEFAULT_FONT_ID 0
#define DEFAULT_MINECRAFT_FONT_ID 1

#define DEBUG

class Engine {

private:
    Engine();
    class SceneHandler* m_pSceneHandler;
    class InputHandler* m_pInputHandler;
    class FontHandler*  m_pFontHandler;
    class BasicCommandHandler* m_pBasicCommandHandler;
    bool m_bRunning = false;
    uint32_t m_millisecondsLastFrame = 0;

public:
    ~Engine();
	void Start();
	void End();
	void Init();

    class SceneHandler& GetSceneHandler();
    class InputHandler& GetInputHandler();
    class FontHandler& GetFontHandler();
    class BasicCommandHandler& GetBasicCommandHandler();

    static Engine& Get()
	{
        static Engine s_instance;
        return s_instance;
	}

    Engine(Engine const&)	  = delete;
    void operator=(Engine const&) = delete;

};

#endif /* _ENGINE_H_ */

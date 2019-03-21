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

#include "globals.h"
#include "utils/GameHelper.h"
#include "utils/ColorHelper.h"
#include "utils/iniconfig.h"
#include "commands/client/SwitchToIntroCommand.h"
#include "commands/client/SwitchToMainMenuCommand.h"

#include "input/InputHandler.h"
#include "scenes/SceneHandler.h"
#include "font/FontHandler.h"
#include "commands/BasicCommandHandler.h"

class Engine {

private:
    Engine();
    class SceneHandler* m_pSceneHandler;
    class InputHandler* m_pInputHandler;
    class FontHandler*  m_pFontHandler;
    class BasicCommandHandler* m_pBasicCommandHandler;
    IniConfig m_iniConfig;
    bool m_bRunning = false;
    uint64_t m_millisecondsLastFrame = 0;

public:
    ~Engine();
	void Start();
	void End();
    void Init();

    class SceneHandler& GetSceneHandler();
    class InputHandler& GetInputHandler();
    class FontHandler& GetFontHandler();
    class BasicCommandHandler& GetBasicCommandHandler();
    class SpriteStageManager& GetSpriteStageManager();        
    inline IniConfig& GetIniConfig() { return m_iniConfig; }

    static Engine& Get()
	{
        static Engine s_instance;
        return s_instance;
	}

    Engine(Engine const&)	  = delete;
    void operator=(Engine const&) = delete;
private:
    void ParseIniFile();

};

#endif /* _ENGINE_H_ */

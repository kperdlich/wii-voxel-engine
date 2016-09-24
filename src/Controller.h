/*
 * Controller.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

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

//#define DEBUG

class Controller {

private:
	Controller();
	class SceneHandler* m_sceneHandler;
	class InputHandler* m_inputHandler;
	class FontHandler*  m_fontHandler;
	class CBasicCommandHandler* m_basicCommandHandler;
	bool m_Running;

public:
	~Controller();
	void Start();
	void End();
	void Init();
	void SwitchToNextScene();
	class SceneHandler& GetSceneHandler();
	class InputHandler& GetInputHandler();
	class FontHandler& GetFontHandler();
	class CBasicCommandHandler& GetBasicCommandHandler();

	static Controller& GetInstance()
	{
		static Controller instance;
		return instance;
	}

	Controller(Controller const&)	  = delete;
	void operator=(Controller const&) = delete;

};

#endif /* _CONTROLLER_H_ */

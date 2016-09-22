/*
 * Controller.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef SRC_HANDLER_CONTROLLER_H_
#define SRC_HANDLER_CONTROLLER_H_

#include "../utils/GameHelper.h"
#include "../gui/ColorHelper.h"
#include "../commands/client/SwitchToIntroCommand.h"
#include "../commands/client/SwitchToMainMenuCommand.h"

#include "InputHandler.h"
#include "SceneHandler.h"
#include "FontHandler.h"
#include "BasicCommandHandler.h"

#define DEFAULT_FONT_ID 0
#define DEFAULT_MINECRAFT_FONT_ID 1

#define DEBUG

class SceneHandler;
class InputHandler;
class FontHandler;
class CBasicCommandHandler;

class Controller {

private:
	Controller();
	SceneHandler* m_sceneHandler;
	InputHandler* m_inputHandler;
	FontHandler*  m_fontHandler;
	CBasicCommandHandler* m_basicCommandHandler;
	bool m_Running;

public:
	~Controller();
	void start();
	void end();
	void init();
	void switchToNextScene();
	SceneHandler* getSceneHandler();
	InputHandler* getInputHandler();
	FontHandler* getFontHandler();
	CBasicCommandHandler* getBasicCommandHandler();

	static Controller& getInstance()
	{
		static Controller instance;
		return instance;
	}

	Controller(Controller const&)	  = delete;
	void operator=(Controller const&) = delete;

};

#endif /* SRC_HANDLER_CONTROLLER_H_ */

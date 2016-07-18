/*
 * Controller.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */



#include "Controller.h"
#include "../utils/Debug.h"

static char* pLoadedTextureLogBuffer;
static char* pResolutionLogBuffer;

Controller::Controller() {
	m_Running = false;
	m_sceneHandler = new SceneHandler();
	m_inputHandler = new InputHandler();
	m_fontHandler = new FontHandler();
	m_basicCommandHandler = new CBasicCommandHandler();

#ifdef DEBUG
	pLoadedTextureLogBuffer = new char[50];
	pResolutionLogBuffer = new char[30];
#endif
}

Controller::~Controller() {

}



void Controller::start()
{
	m_Running = true;

	init();

	m_basicCommandHandler->executeCommand( SwitchToIntroCommand::Name() );

	while( m_Running )
	{
		GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

		m_inputHandler->update();
		m_sceneHandler->update();
		m_sceneHandler->drawScene();

#ifdef DEBUG
		printGameVersion(0, 25, m_fontHandler->getNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE );
		printFps( 500, 25, m_fontHandler->getNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_YELLOW );



		sprintf(pResolutionLogBuffer, "Resolution x: %d y: %d", rmode->viWidth, rmode->viHeight );
		Debug::getInstance().log(pResolutionLogBuffer);


		sprintf(pLoadedTextureLogBuffer, "Loaded Textures in scene: %d", m_sceneHandler->getCurrentScene()->getTextureHandler()->TextureCount());
		Debug::getInstance().log( pLoadedTextureLogBuffer );

		Debug::getInstance().print();
		Debug::getInstance().clear();
#endif

		GRRLIB_Render();
		calculateFrameRate();
	}

	delete m_basicCommandHandler;
	delete m_sceneHandler;
	delete m_inputHandler;
	delete m_fontHandler;

#ifdef DEBUG
	delete [] pResolutionLogBuffer;
	delete [] pLoadedTextureLogBuffer;
#endif

	GRRLIB_Exit();
}

void Controller::end() {
	m_Running = false;
}

void Controller::init() {

	GRRLIB_Init();
	GRRLIB_Settings.antialias = true;

	m_fontHandler->init();
	m_inputHandler->init();
	m_sceneHandler->init();
	m_basicCommandHandler->init();
}

void Controller::switchToNextScene() {
	m_sceneHandler->loadNextScene();
}

SceneHandler* Controller::getSceneHandler() {
	return m_sceneHandler;
}

InputHandler* Controller::getInputHandler() {
	return m_inputHandler;
}

FontHandler* Controller::getFontHandler() {
	return m_fontHandler;
}

CBasicCommandHandler* Controller::getBasicCommandHandler() {
	return m_basicCommandHandler;
}

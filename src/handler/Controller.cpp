/*
 * Controller.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */



#include "Controller.h"
#include "../utils/Debug.h"


Controller::Controller() {
	m_Running = false;
	m_sceneHandler = new SceneHandler();
	m_inputHandler = new InputHandler();
	m_fontHandler = new FontHandler();
	m_basicCommandHandler = new CBasicCommandHandler();
}

Controller::~Controller() {

}



void Controller::start()
{
	m_Running = true;

	init();

	m_basicCommandHandler->executeCommand( SwitchToIntroCommand::Name() );

	while( m_Running ) {

		m_inputHandler->update();

		GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

		m_sceneHandler->update();
		m_sceneHandler->drawScene();
		//GRRLIB_DrawImg( (rmode->viWidth / 2) - (logoTex->GetWidth() / 2) , (rmode->viHeight / 2) - ( logoTex->GetHeight() / 2 ), logoTex->GetNativeTexture() , 0, 1, 1, GRRLIB_WHITE);

		printGameVersion(0, 25, m_fontHandler->getNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE );
		printFps( 500, 25, m_fontHandler->getNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_YELLOW );

		char* buffer2 = new char[50];
		sprintf(buffer2, "Resolution x: %d y: %d", rmode->viWidth, rmode->viHeight );
		Debug::getInstance().log( buffer2 );

		std::vector<BasicTexture*>* textures = m_sceneHandler->getCurrentScene()->getTextureHandler()->getTextures();
		char* buffer = new char[50];
		sprintf(buffer, "Loaded Textures in scene: %d", textures->size());
		Debug::getInstance().log( buffer );

		Debug::getInstance().print();
		Debug::getInstance().clear();

		GRRLIB_Render();
		calculateFrameRate();
	}

	delete m_basicCommandHandler;
	delete m_sceneHandler;
	delete m_inputHandler;
	delete m_fontHandler;

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

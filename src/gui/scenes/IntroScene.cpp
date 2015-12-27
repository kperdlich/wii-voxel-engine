/*
 * IntroScene.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#include <grrlib.h>
#include <vector>
#include "IntroScene.h"
#include "../components/UITextureElement.h"
#include "../../commands/client/SwitchToMainMenuCommand.h"

#include "../../utils/Debug.h"
#include "BlockCSS_png.h"
#include "ClassicBackgroundSprite_png.h"
#include "MinecraftLogo_png.h"


// define all component names here!
#define IS_CLASSIC_BACKGROUND "IS_ClassicBackground"
#define IS_LOGO "IS_Logo"


#define LOGO_INDEX 0

IntroScene::IntroScene()  {

}

IntroScene::~IntroScene() {

}


void IntroScene::load()
{
	m_BackgroundAlpha = 255;
	Texture* logoTexture = m_TextureHandler->createTexture( MinecraftLogo_png);
	m_elements.push_back( new UITextureElement( (rmode->viWidth / 2) - (logoTexture->getWidth() / 2), (rmode->viHeight / 2) - ( logoTexture->getHeight() / 2 ), IS_LOGO,logoTexture));
}


void IntroScene::update() {
	Basic2DScene::update();

	if (m_BackgroundAlpha > 0)
	{
		m_BackgroundAlpha--;
		for ( int i = 0; i < m_elements.size(); i++)
		{
			UITextureElement* element = dynamic_cast<UITextureElement*>(m_elements[i]);
			if (element && element->isVisible())
			{
				element->setColor( 0xFFFFFF00 | m_BackgroundAlpha );
			}
		}
	}
	else
	{
		Controller::getInstance().getBasicCommandHandler()->executeCommand( SwitchToMainMenuCommand::Name() );
	}


	// debug stuff
	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );
	if ( pad->buttonsDown() & WPAD_BUTTON_RIGHT)
	{
		Controller::getInstance().getBasicCommandHandler()->executeCommand( SwitchToMainMenuCommand::Name() );
	}


}

void IntroScene::draw() {
	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
	Basic2DScene::draw();
}

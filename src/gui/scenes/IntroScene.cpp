/*
 * IntroScene.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#include <vector>
#include "IntroScene.h"
#include "../../utils/Debug.h"
#include "../components/Logo.h"
#include "../components/ClassicBackground.h"
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
	//m_elements.push_back( new ClassicBackground( IS_CLASSIC_BACKGROUND, m_TextureHandler->createTexture( ClassicBackgroundSprite_png )));
	m_elements.push_back( new Logo(IS_LOGO , m_TextureHandler->createTexture( MinecraftLogo_png)));


	//SpriteSheet* tex2 = m_TextureHandler->createTilemap( BlockCSS_png );
	//tex->setX( (rmode->viWidth / 2) - (tex->getWidth() / 2) );
	//tex->setY( (rmode->viHeight / 2) - ( tex->getHeight() / 2 ) );
	//SpriteSheet* tex2 = m_TextureHandler->createTilemap( textures_0_png );

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

	WiiPad* pad = Controller::getInstance().getInputHandler()->getPadByID( WII_PAD_0 );
	//Texture* logo = (Texture*) m_TextureHandler->getTextureByID( LOGO_INDEX );
	//logo->setX( pad->getX() );
	//logo->setY( pad->getY() );

	if ( pad->buttonsDown() & WPAD_BUTTON_RIGHT)
	{
		//Controller::GetInstance().GetBasicCommandHandler()->ExecuteCommand( new SwitchToMainMenuCommand() );
		Controller::getInstance().getBasicCommandHandler()->executeCommand( SwitchToMainMenuCommand::Name() );
	}

	/*if ( WPAD_ButtonsDown(0) & WPAD_BUTTON_RIGHT )
	{
		Texture* logo = m_TextureHandler->GetTextureByID( LOGO_POSITION );
		logo->SetX( logo->GetX() + 1 );
	}
	if ( WPAD_ButtonsDown(0) & WPAD_BUTTON_LEFT )
	{
		Texture* logo = m_TextureHandler->GetTextureByID( LOGO_POSITION );
		logo->SetX( logo->GetX() - 1 );
	}*/

}

void IntroScene::draw() {
	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
	Basic2DScene::draw();
	//GRRLIB_DrawTile( 200, 300, tex2->getNativeTexture(), 90, 10, 10, GRRLIB_WHITE, 27 );
}

/*
 * IntroScene.cpp
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#include "../core/grrlib.h"
#include <vector>
#include "IntroScene.h"
#include "../components/UITextureElement.h"
#include "../commands/client/SwitchToMainMenuCommand.h"

#include "../utils/Debug.h"
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


void IntroScene::Load()
{
	Basic2DScene::Load();
	m_BackgroundAlpha = 255;
	Texture* logoTexture = m_TextureHandler->CreateTexture( MinecraftLogo_png, IS_LOGO);
	m_elements.push_back( new UITextureElement( (rmode->viWidth / 2) - (logoTexture->GetWidth() / 2), (rmode->viHeight / 2) - ( logoTexture->GetHeight() / 2 ), IS_LOGO,logoTexture));
}


void IntroScene::Update() {
	Basic2DScene::Update();

	if (m_BackgroundAlpha > 0)
	{
		m_BackgroundAlpha--;
		for ( unsigned int i = 0; i < m_elements.size(); i++)
		{
			UITextureElement* element = dynamic_cast<UITextureElement*>(m_elements[i]);
			if (element && element->IsVisible())
			{
				element->SetColor( 0xFFFFFF00 | m_BackgroundAlpha );
			}
		}
	}
	else
	{
		Controller::GetInstance().GetBasicCommandHandler().ExecuteCommand( SwitchToMainMenuCommand::Name() );
	}


	WiiPad* pad = Controller::GetInstance().GetInputHandler().GetPadByID( WII_PAD_0 );
	if ( pad->ButtonsDown() & WPAD_BUTTON_RIGHT)
	{
		Controller::GetInstance().GetBasicCommandHandler().ExecuteCommand( SwitchToMainMenuCommand::Name() );
	}
}

void IntroScene::Draw() {
	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
	Basic2DScene::Draw();
}

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

#include "MainMenuScene.h"
#include "../components/Cursor.h"
#include "../components/UITextureElement.h"
#include "../components/List.h"
#include "../utils/Debug.h"
#include "Cursor_png.h"
#include "ClassicBackgroundSprite_png.h"
#include "BasicButtonBig_png.h"
#include "BasicButtonBigHighlight_png.h"
#include "WoxelCraft_png.h"
#include "WoxelCraft_png.h"

#include "Hotbar_png.h"
#include <string.h>

// define all scene components here
#define MMS_BUTTON_SINGLEPLAYER "MMS_btnSingleplayer"
#define MMS_BUTTON_MULTIPLAYER "MMS_btnMultiplayer"
#define MMS_BUTTON_OPTION "MMS_btnOption"
#define MMS_BUTTON_EXIT "MMS_btnExit"
#define MMS_CLASSIC_BACKGROUND "MMS_ClassicBackground"
#define MMS_LOGO "MMS_Logo"
#define MMS_CURSOR "MMS_Cursor"

#define LABEL_TAG "label"
#define HIGHLIGHT_TAG "highlight"

#define BUTTON_Y_DISTANCE 5


static void OnStartSingleplayer(BasicButton* clickedButton)
{
	Controller::GetInstance().GetBasicCommandHandler().ExecuteCommand( SwitchToInGameCommand::Name() );
}

static void OnExitGame(BasicButton* clickedButton)
{
	Controller::GetInstance().End();
}


MainMenuScene::MainMenuScene() {

}

MainMenuScene::~MainMenuScene() {

}

void MainMenuScene::Load() {
	Basic2DScene::Load();
	m_elements.push_back( new UITextureElement( MMS_CLASSIC_BACKGROUND , m_TextureHandler->CreateTexture( ClassicBackgroundSprite_png, MMS_CLASSIC_BACKGROUND )));
	UITextureElement* logo = new UITextureElement( MMS_LOGO , m_TextureHandler->CreateTexture( WoxelCraft_png, MMS_LOGO));
	logo->SetX( (rmode->viWidth / 2) - (logo->GetWidth() / 2) );
	logo->SetY( 30 );
	m_elements.push_back( logo );

	CreateMainMenuButtonList();

	m_elements.push_back( new Cursor( MMS_CURSOR , m_TextureHandler->CreateTexture( Cursor_png, MMS_CURSOR )));
}

void MainMenuScene::Draw() {
	GRRLIB_SetBackgroundColour(0x24, 0x5E, 0x23, 1);
	Basic2DScene::Draw();
}

void MainMenuScene::Update() {
	Basic2DScene::Update();

#ifdef DEBUG
	WiiPad* pad = Controller::GetInstance().GetInputHandler().GetPadByID( WII_PAD_0 );
	if ( pad->ButtonsDown() & WPAD_BUTTON_LEFT)
	{
		Controller::GetInstance().GetBasicCommandHandler().ExecuteCommand( SwitchToIntroCommand::Name() );
	}
	else if ( pad->ButtonsDown() & WPAD_BUTTON_RIGHT )
	{
		Controller::GetInstance().GetBasicCommandHandler().ExecuteCommand( SwitchToInGameCommand::Name() );
	}
#endif

}

void MainMenuScene::CreateMainMenuButtonList()
{
	Texture* startButtonTexture = m_TextureHandler->CreateTexture( BasicButtonBig_png, "BasicButtonBig_png" );
	int xPos = (rmode->viWidth / 2) - (startButtonTexture->GetWidth() / 2);
	int yPos = (rmode->viHeight / 2) - ( startButtonTexture->GetHeight() / 2 );
	int sizeBetweenBtns = startButtonTexture->GetHeight() + BUTTON_Y_DISTANCE;
	m_TextureHandler->DestroyTextureByName("BasicButtonBig_png");

	List* btnList = new List( xPos, yPos, sizeBetweenBtns );
	btnList->AddComponent( CreateDefaultMainMenuButton( MMS_BUTTON_SINGLEPLAYER, "Singleplayer", &OnStartSingleplayer ));
	btnList->AddComponent( CreateDefaultMainMenuButton( MMS_BUTTON_MULTIPLAYER, "Multiplayer", NULL ));
	btnList->AddComponent( CreateDefaultMainMenuButton( MMS_BUTTON_OPTION, "Option", NULL ));
	btnList->AddComponent( CreateDefaultMainMenuButton( MMS_BUTTON_EXIT, "Exit", &OnExitGame));
	m_elements.push_back(btnList);
}


BasicButton* MainMenuScene::CreateDefaultMainMenuButton(  const char* buttonName, const char* buttontext, void (*clickCallback) (BasicButton*) )
{
	FontHandler& fontHandler = Controller::GetInstance().GetFontHandler();

	Texture* pdefaultButtonTexture = m_TextureHandler->CreateTexture( BasicButtonBig_png, buttonName);

	char searchNamehighlight[strlen(buttonName) + strlen(HIGHLIGHT_TAG) +1];
	strcpy( searchNamehighlight, buttonName );
	strcat( searchNamehighlight, HIGHLIGHT_TAG );
	Texture* pHighlightButtonTexture = m_TextureHandler->CreateTexture( BasicButtonBigHighlight_png, searchNamehighlight );

	char searchLabel[strlen(buttonName) + strlen(LABEL_TAG) +1];
	strcpy( searchLabel, buttonName );
	strcat( searchLabel, LABEL_TAG );
	LabelTexture* pButtonLabel = m_TextureHandler->CreateLabel( buttontext, fontHandler.GetNativFontByID( DEFAULT_MINECRAFT_FONT_ID ), searchLabel);

	return new BasicButton( 0, 0, buttonName, pdefaultButtonTexture, pHighlightButtonTexture, pButtonLabel, clickCallback );
}


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
#include "../components/UiTextureElement.h"
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
#define MMS_BUTTON_SINGLEPLAYER  "MMS_btnSingleplayer"
#define MMS_BUTTON_MULTIPLAYER   "MMS_btnMultiplayer"
#define MMS_BUTTON_OPTION        "MMS_btnOption"
#define MMS_BUTTON_EXIT          "MMS_btnExit"
#define MMS_CLASSIC_BACKGROUND   "MMS_ClassicBackground"
#define MMS_LOGO                 "MMS_Logo"
#define MMS_CURSOR               "MMS_Cursor"

#define LABEL_TAG                "label"
#define HIGHLIGHT_TAG            "highlight"

#define BUTTON_Y_DISTANCE        5

// Sorting Layers
#define BACKGROUND_SORTING_LAYER 0
#define COMPONENTS_SORTING_LAYER 1
#define LABEL_SORTING_LAYER      2
#define CURSOR_SORTING_LAYER     3

CMainMenuScene::CMainMenuScene() {

}

CMainMenuScene::~CMainMenuScene() {

}

void CMainMenuScene::Load()
{
    Basic2DScene::Load();
    m_elements.push_back( new UiTextureElement( MMS_CLASSIC_BACKGROUND , m_TextureHandler->CreateSprite(ClassicBackgroundSprite_png, ClassicBackgroundSprite_png_size, MMS_CLASSIC_BACKGROUND, BACKGROUND_SORTING_LAYER )));
    UiTextureElement* logo = new UiTextureElement( MMS_LOGO , m_TextureHandler->CreateSprite(WoxelCraft_png, WoxelCraft_png_size, MMS_LOGO, COMPONENTS_SORTING_LAYER));
	logo->SetX( (rmode->viWidth / 2) - (logo->GetWidth() / 2) );
	logo->SetY( 60 );
	m_elements.push_back( logo );

	CreateMainMenuButtonList();

    m_elements.push_back( new Cursor( MMS_CURSOR , m_TextureHandler->CreateSprite(Cursor_png, Cursor_png_size, MMS_CURSOR, CURSOR_SORTING_LAYER )));
}

void CMainMenuScene::Draw()
{
    GRRLIB_SetBackgroundColour(0x24, 0x5E, 0x23, 1);
    Basic2DScene::Draw();
}

void CMainMenuScene::Update(float deltaSeconds)
{
    Basic2DScene::Update(deltaSeconds);

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

void CMainMenuScene::CreateMainMenuButtonList()
{
    auto startButtonTexture = m_TextureHandler->CreateSprite(BasicButtonBig_png, BasicButtonBig_png_size, "BasicButtonBig_png" );
	int xPos = (rmode->viWidth / 2) - (startButtonTexture->GetWidth() / 2);
	int yPos = (rmode->viHeight / 2) - ( startButtonTexture->GetHeight() / 2);
	int sizeBetweenBtns = startButtonTexture->GetHeight() + BUTTON_Y_DISTANCE;
    m_TextureHandler->DestroySpriteByName("BasicButtonBig_png");


	List* btnList = new List( xPos, yPos, sizeBetweenBtns );
    btnList->AddComponent( CreateDefaultMainMenuButton( MMS_BUTTON_SINGLEPLAYER, "Singleplayer", [] (BasicButton* clickedButton) { Controller::GetInstance().GetBasicCommandHandler().ExecuteCommand(SwitchToInGameCommand::Name()); }));
    btnList->AddComponent( CreateDefaultMainMenuButton( MMS_BUTTON_MULTIPLAYER, "Multiplayer", nullptr ));
    btnList->AddComponent( CreateDefaultMainMenuButton( MMS_BUTTON_OPTION, "Option", nullptr ));
    btnList->AddComponent( CreateDefaultMainMenuButton( MMS_BUTTON_EXIT, "Exit", [] (BasicButton* clickedButton) { Controller::GetInstance().End(); }));
	m_elements.push_back(btnList);
}


BasicButton* CMainMenuScene::CreateDefaultMainMenuButton( const char* buttonName, const char* buttontext, void (*clickCallback) (BasicButton*) )
{
    FontHandler& fontHandler = Controller::GetInstance().GetFontHandler();

    auto pdefaultButtonTexture = m_TextureHandler->CreateSprite(BasicButtonBig_png, BasicButtonBig_png_size, buttonName, COMPONENTS_SORTING_LAYER);

	char searchNamehighlight[strlen(buttonName) + strlen(HIGHLIGHT_TAG) +1];
	strcpy( searchNamehighlight, buttonName );
	strcat( searchNamehighlight, HIGHLIGHT_TAG );
    auto pHighlightButtonTexture = m_TextureHandler->CreateSprite(BasicButtonBigHighlight_png, BasicButtonBigHighlight_png_size, searchNamehighlight, COMPONENTS_SORTING_LAYER);

	char searchLabel[strlen(buttonName) + strlen(LABEL_TAG) +1];
	strcpy( searchLabel, buttonName );
	strcat( searchLabel, LABEL_TAG );
    auto pButtonLabel = m_TextureHandler->CreateLabel( buttontext, fontHandler.GetNativFontByID( DEFAULT_MINECRAFT_FONT_ID ), searchLabel, LABEL_SORTING_LAYER);

	return new BasicButton( 0, 0, buttonName, pdefaultButtonTexture, pHighlightButtonTexture, pButtonLabel, clickCallback );
}


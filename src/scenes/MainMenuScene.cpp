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

#include <string>
#include "scenes/MainMenuScene.h"
#include "components/Cursor.h"
#include "components/UiTextureElement.h"
#include "components/List.h"
#include "utils/Debug.h"
#include "Cursor_png.h"
#include "ClassicBackgroundSprite_png.h"
#include "BasicButtonBig_png.h"
#include "BasicButtonBigHighlight_png.h"
#include "WoxelCraft_png.h"
#include "WoxelCraft_png.h"

#include "Hotbar_png.h"

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

void MainMenuScene::Load()
{    
    m_elements.push_back(new UiTextureElement(MMS_CLASSIC_BACKGROUND,
                                              Sprite::Create(ClassicBackgroundSprite_png, ClassicBackgroundSprite_png_size,
                                                             MMS_CLASSIC_BACKGROUND, BACKGROUND_SORTING_LAYER)));
    UiTextureElement* logo = new UiTextureElement(MMS_LOGO,
                                                  Sprite::Create(WoxelCraft_png, WoxelCraft_png_size, MMS_LOGO, COMPONENTS_SORTING_LAYER));
    logo->SetX((rmode->viWidth / 2) - (logo->GetWidth() / 2));
    logo->SetY(60);
	m_elements.push_back( logo );

    CreateMainMenuButtonList();

    m_elements.push_back(new Cursor(MMS_CURSOR, Sprite::Create(Cursor_png, Cursor_png_size, MMS_CURSOR, CURSOR_SORTING_LAYER)));
    Basic2DScene::Load();
}

void MainMenuScene::Draw()
{
    GRRLIB_SetBackgroundColour(0x24, 0x5E, 0x23, 1);
    Basic2DScene::Draw();
}

void MainMenuScene::Update(float deltaSeconds)
{
    Basic2DScene::Update(deltaSeconds);
#ifdef DEBUG
    WiiPad* pad = Engine::Get().GetInputHandler().GetPadByID(WII_PAD_0);
    if (pad->ButtonsDown() & WPAD_BUTTON_LEFT)
	{
        Engine::Get().GetBasicCommandHandler().ExecuteCommand(SwitchToIntroCommand::Name());
	}
    else if (pad->ButtonsDown() & WPAD_BUTTON_RIGHT)
	{
        Engine::Get().GetBasicCommandHandler().ExecuteCommand(SwitchToInGameCommand::Name());
    }
#endif   

}

void MainMenuScene::CreateMainMenuButtonList()
{
    auto startButtonTexture = Sprite::Create(BasicButtonBig_png, BasicButtonBig_png_size, "BasicButtonBig_png" );
	int xPos = (rmode->viWidth / 2) - (startButtonTexture->GetWidth() / 2);
	int yPos = (rmode->viHeight / 2) - ( startButtonTexture->GetHeight() / 2);
	int sizeBetweenBtns = startButtonTexture->GetHeight() + BUTTON_Y_DISTANCE;    
    delete startButtonTexture;

    List* btnList = new List(xPos, yPos, sizeBetweenBtns);

    btnList->AddComponent(CreateDefaultMainMenuButton(MMS_BUTTON_SINGLEPLAYER, "Singleplayer",
                                                      [] (BasicButton* clickedButton)
                                                      {
                                                        Engine::Get().GetBasicCommandHandler().ExecuteCommand(SwitchToInGameCommand::Name());
                                                      }));
    btnList->AddComponent(CreateDefaultMainMenuButton(MMS_BUTTON_MULTIPLAYER, "Multiplayer",
                                                      [] (BasicButton* clickedButton)
                                                      {
                                                        Engine::Get().GetBasicCommandHandler().ExecuteCommand(SwitchToInGameCommand::Name());
                                                      }));
    btnList->AddComponent(CreateDefaultMainMenuButton(MMS_BUTTON_OPTION, "Option", nullptr ));
    btnList->AddComponent(CreateDefaultMainMenuButton(MMS_BUTTON_EXIT, "Exit",
                                                      [] (BasicButton* clickedButton)
                                                      {
                                                        Engine::Get().End();
                                                      }));
    m_elements.push_back(btnList);
}


BasicButton* MainMenuScene::CreateDefaultMainMenuButton(const char* buttonName, const char* buttontext, std::function<void(BasicButton*)> clickCallback)
{
    FontHandler& fontHandler = Engine::Get().GetFontHandler();

    auto pdefaultButtonTexture = Sprite::Create(BasicButtonBig_png, BasicButtonBig_png_size, buttonName, COMPONENTS_SORTING_LAYER);

    std::string searchNamehighlight = std::string(buttonName).append(HIGHLIGHT_TAG);
    auto pHighlightButtonTexture = Sprite::Create(BasicButtonBigHighlight_png, BasicButtonBigHighlight_png_size, searchNamehighlight, COMPONENTS_SORTING_LAYER);

    std::string searchLabel = std::string(buttonName).append(LABEL_TAG);
    auto pButtonLabel = Label::Create(buttontext, fontHandler.GetNativFontByID(DEFAULT_MINECRAFT_FONT_ID), searchLabel, LABEL_SORTING_LAYER);

    return new BasicButton(0, 0, buttonName, pdefaultButtonTexture, pHighlightButtonTexture, pButtonLabel, clickCallback);
}


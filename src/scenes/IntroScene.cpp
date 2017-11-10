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

#include "../core/grrlib.h"
#include <vector>
#include <math.h>
#include "IntroScene.h"
#include "../components/UiTextureElement.h"
#include "../commands/client/SwitchToMainMenuCommand.h"

#include "../utils/Debug.h"
#include "BlockCSS_png.h"
#include "ClassicBackgroundSprite_png.h"
#include "WoxelCraft_png.h"

// define all component names here!
#define IS_CLASSIC_BACKGROUND "IS_ClassicBackground"
#define IS_LOGO "IS_Logo"

#define LOGO_INDEX 0

CIntroScene::CIntroScene()  {

}

CIntroScene::~CIntroScene() {

}


void CIntroScene::Load()
{
    Basic2DScene::Load();
	m_BackgroundAlpha = 255;
    auto logoSprite = m_TextureHandler->CreateSprite(WoxelCraft_png, WoxelCraft_png_size, IS_LOGO);
    m_elements.push_back( new UiTextureElement( (rmode->viWidth / 2) - (logoSprite->GetWidth() / 2), (rmode->viHeight / 2) - ( logoSprite->GetHeight() / 2 ), IS_LOGO, logoSprite));
}


void CIntroScene::Update(float deltaSeconds)
{
    Basic2DScene::Update(deltaSeconds);

	if (m_BackgroundAlpha > 0)
	{
        m_BackgroundAlpha -= deltaSeconds * 10;
        for ( uint32_t i = 0; i < m_elements.size(); i++)
		{
			UiTextureElement* element = dynamic_cast<UiTextureElement*>(m_elements[i]);
			if (element && element->IsVisible())
			{
				element->SetColor( 0xFFFFFF00 | m_BackgroundAlpha );
			}
		}
	}
	else
	{
        Engine::Get().GetBasicCommandHandler().ExecuteCommand( SwitchToMainMenuCommand::Name() );
	}


    WiiPad* pad = Engine::Get().GetInputHandler().GetPadByID( WII_PAD_0 );
	if ( pad->ButtonsDown() & WPAD_BUTTON_RIGHT)
	{
        Engine::Get().GetBasicCommandHandler().ExecuteCommand( SwitchToMainMenuCommand::Name() );
    }
}

void CIntroScene::Draw()
{
	GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
    Basic2DScene::Draw();
}

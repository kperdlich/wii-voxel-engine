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


#include "Controller.h"
#include <ogc/lwp_watchdog.h>
#include "utils/Debug.h"


Controller::Controller()
{
    m_bRunning = false;
    m_pSceneHandler = new SceneHandler();
    m_pInputHandler = new InputHandler();
    m_pFontHandler = new FontHandler();
    m_pBasicCommandHandler = new BasicCommandHandler();
}

Controller::~Controller() {}


void Controller::Start()
{
    m_bRunning = true;

	Init();

    m_pBasicCommandHandler->ExecuteCommand( SwitchToIntroCommand::Name() );

    while( m_bRunning )
    {
        uint32_t startFrameTime = ticks_to_millisecs(gettime());

        GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

        m_pInputHandler->Update();        
        m_pSceneHandler->Update(m_millisecondsDeltaLastFrame / 1000.0f);
        m_pSceneHandler->DrawScene();

        PrintFps( 500, 25, m_pFontHandler->GetNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_YELLOW );

#ifdef DEBUG
        PrintGameVersion(0, 25, m_pFontHandler->GetNativFontByID( DEFAULT_FONT_ID ), DEFAULT_FONT_SIZE, GRRLIB_WHITE );

        Debug::GetInstance().Log("Resolution x: %d y: %d", rmode->viWidth, rmode->viHeight);
        Debug::GetInstance().Log( "Loaded Textures in scene: %d", m_pSceneHandler->GetCurrentScene().GetTextureHandler().TextureCount() );

        Debug::GetInstance().Print();
        Debug::GetInstance().Reset();
#endif

        GRRLIB_Render();
        CalculateFrameRate();

        m_millisecondsDeltaLastFrame = ticks_to_millisecs(gettime()) - startFrameTime;
	}

    delete m_pBasicCommandHandler;
    delete m_pSceneHandler;
    delete m_pInputHandler;
    delete m_pFontHandler;

#ifdef DEBUG	
    Debug::GetInstance().Destroy();
#endif

	GRRLIB_Exit();
}

void Controller::End()
{
    m_bRunning = false;
}

void Controller::Init()
{

	GRRLIB_Init();
	GRRLIB_Settings.antialias = true;

    m_pFontHandler->Init();
    m_pInputHandler->Init();
    m_pSceneHandler->Init();
    m_pBasicCommandHandler->Init();
}


void Controller::SwitchToNextScene()
{
    m_pSceneHandler->LoadNextScene();
}

SceneHandler& Controller::GetSceneHandler()
{
    return *m_pSceneHandler;
}

InputHandler& Controller::GetInputHandler()
{
    return *m_pInputHandler;
}

FontHandler& Controller::GetFontHandler()
{
    return *m_pFontHandler;
}

BasicCommandHandler& Controller::GetBasicCommandHandler()
{
    return *m_pBasicCommandHandler;
}

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

#include "SkyBox.h"
#include "../utils/RenderHelper.h"
#include "../utils/Vector3.h"

#include "SkyBox_Top_png.h"
#include "SkyBox_Left_png.h"
#include "SkyBox_Right_png.h"
#include "SkyBox_Bottom_png.h"
#include "SkyBox_Front_png.h"
#include "SkyBox_Back_png.h"


#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5

#define PLAYER_DISTANCE 120.0f
#define SKYBOX_FACES 6

SkyBox::SkyBox()
{
	for ( uint32_t i = 0; i < 6; i++)
	{
        m_pSkyBoxTextures[i] = nullptr;
	}
}

SkyBox::~SkyBox()
{
	if ( m_DisplayListSize > 0 )
	{
		free(m_pDispList);
		m_DisplayListSize = 0;
        m_pDispList = nullptr;
	}
}

void SkyBox::Init()
{
	m_pSkyBoxTextures[SKY_FRONT] = Controller::GetInstance().GetSceneHandler().GetCurrentScene().GetTextureHandler().CreateTexture(SkyBox_Front_png, "SKY_FRONT", false);
	m_pSkyBoxTextures[SKY_RIGHT] = Controller::GetInstance().GetSceneHandler().GetCurrentScene().GetTextureHandler().CreateTexture(SkyBox_Right_png, "SKY_RIGHT", false);
	m_pSkyBoxTextures[SKY_LEFT] = Controller::GetInstance().GetSceneHandler().GetCurrentScene().GetTextureHandler().CreateTexture(SkyBox_Left_png, "SKY_LEFT", false);
	m_pSkyBoxTextures[SKY_BACK] = Controller::GetInstance().GetSceneHandler().GetCurrentScene().GetTextureHandler().CreateTexture(SkyBox_Back_png, "SKY_BACK", false);
	m_pSkyBoxTextures[SKY_UP] = Controller::GetInstance().GetSceneHandler().GetCurrentScene().GetTextureHandler().CreateTexture(SkyBox_Top_png, "SKY_UP", false);
	m_pSkyBoxTextures[SKY_DOWN] = Controller::GetInstance().GetSceneHandler().GetCurrentScene().GetTextureHandler().CreateTexture(SkyBox_Bottom_png, "SKY_DOWN", false);

	CreateSkyBox();
}

void SkyBox::CreateSkyBox()
{
    size_t size = RenderHelper::GetDisplayListSizeForFaces(SKYBOX_FACES);
	m_pDispList = memalign(32, size);
	memset(m_pDispList, 0, size);
	DCInvalidateRange(m_pDispList, size);
	GX_BeginDispList(m_pDispList, size);

	GX_SetCullMode(GX_CULL_BACK);

    GRRLIB_SetTexture(m_pSkyBoxTextures[SKY_RIGHT]->GetNativeTexture(), true, false);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(PLAYER_DISTANCE,PLAYER_DISTANCE,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,0);
		GX_Position3f32(PLAYER_DISTANCE,PLAYER_DISTANCE,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,0);
		GX_Position3f32(PLAYER_DISTANCE,0,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,1);
		GX_Position3f32(PLAYER_DISTANCE,0,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,1);
	GX_End();

    GRRLIB_SetTexture(m_pSkyBoxTextures[SKY_FRONT]->GetNativeTexture(), true, false);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0,PLAYER_DISTANCE,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,0);
		GX_Position3f32(PLAYER_DISTANCE,PLAYER_DISTANCE,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,0);
		GX_Position3f32(PLAYER_DISTANCE,0,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,1);
		GX_Position3f32(0,0,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,1);
	GX_End();


    GRRLIB_SetTexture(m_pSkyBoxTextures[SKY_UP]->GetNativeTexture(), true, false);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0,PLAYER_DISTANCE,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,0);
		GX_Position3f32(0,PLAYER_DISTANCE,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,0);
		GX_Position3f32(PLAYER_DISTANCE,PLAYER_DISTANCE,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,1);
		GX_Position3f32(PLAYER_DISTANCE,PLAYER_DISTANCE,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,1);
	GX_End();

	GX_SetCullMode(GX_CULL_FRONT);

    GRRLIB_SetTexture(m_pSkyBoxTextures[SKY_LEFT]->GetNativeTexture(), true, false);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0,PLAYER_DISTANCE,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,0);
		GX_Position3f32(0,PLAYER_DISTANCE,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,0);
		GX_Position3f32(0,0,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,1);
		GX_Position3f32(0,0,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,1);
	GX_End();

    GRRLIB_SetTexture(m_pSkyBoxTextures[SKY_BACK]->GetNativeTexture(), true, false);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0,PLAYER_DISTANCE,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,0);
		GX_Position3f32(PLAYER_DISTANCE,PLAYER_DISTANCE,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,0);
		GX_Position3f32(PLAYER_DISTANCE,0,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,1);
		GX_Position3f32(0,0,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,1);
	GX_End();

    GRRLIB_SetTexture(m_pSkyBoxTextures[SKY_DOWN]->GetNativeTexture(), true, false);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0,0,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,1);
		GX_Position3f32(0,0,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,1);
		GX_Position3f32(PLAYER_DISTANCE,0,PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0,0);
		GX_Position3f32(PLAYER_DISTANCE,0,0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1,0);
	GX_End();

	GX_SetCullMode(GX_CULL_BACK);

	m_DisplayListSize = GX_EndDispList();
}



void SkyBox::Render()
{
	if ( m_DisplayListSize > 0 )
	{
		GX_CallDispList(m_pDispList, m_DisplayListSize);
	}
}


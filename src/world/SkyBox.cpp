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
#include "../renderer/MasterRenderer.h"
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
    for ( uint8_t i = 0; i < 6; i++)
	{
        m_pSkyBoxTextures[i] = nullptr;
	}
}

SkyBox::~SkyBox()
{
    if ( m_displayListSize > 0 )
	{
		free(m_pDispList);
        m_displayListSize = 0;
        m_pDispList = nullptr;
	}
}

void SkyBox::Init()
{
    auto textureHandler = Controller::GetInstance().GetSceneHandler().GetCurrentScene().GetTextureHandler();

    m_pSkyBoxTextures[SKY_FRONT] = textureHandler.CreateTexture(SkyBox_Front_png, SkyBox_Front_png_size, "SKY_FRONT");
    m_pSkyBoxTextures[SKY_RIGHT] = textureHandler.CreateTexture(SkyBox_Right_png, SkyBox_Right_png_size, "SKY_RIGHT");
    m_pSkyBoxTextures[SKY_LEFT] = textureHandler.CreateTexture(SkyBox_Left_png, SkyBox_Left_png_size, "SKY_LEFT");
    m_pSkyBoxTextures[SKY_BACK] = textureHandler.CreateTexture(SkyBox_Back_png, SkyBox_Back_png_size, "SKY_BACK");
    m_pSkyBoxTextures[SKY_UP] = textureHandler.CreateTexture(SkyBox_Top_png, SkyBox_Top_png_size, "SKY_UP");
    m_pSkyBoxTextures[SKY_DOWN] = textureHandler.CreateTexture(SkyBox_Bottom_png, SkyBox_Bottom_png_size, "SKY_DOWN");

	CreateSkyBox();
}

void SkyBox::CreateSkyBox()
{
    size_t size = MasterRenderer::GetDisplayListSizeForFaces(SKYBOX_FACES);
	m_pDispList = memalign(32, size);
	memset(m_pDispList, 0, size);
	DCInvalidateRange(m_pDispList, size);
	GX_BeginDispList(m_pDispList, size);

	GX_SetCullMode(GX_CULL_BACK);

    MasterRenderer::LoadTexture(*m_pSkyBoxTextures[SKY_RIGHT]);
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

    MasterRenderer::LoadTexture(*m_pSkyBoxTextures[SKY_FRONT]);
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


    MasterRenderer::LoadTexture(*m_pSkyBoxTextures[SKY_UP]);
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

    MasterRenderer::LoadTexture(*m_pSkyBoxTextures[SKY_LEFT]);
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

    MasterRenderer::LoadTexture(*m_pSkyBoxTextures[SKY_BACK]);
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

    MasterRenderer::LoadTexture(*m_pSkyBoxTextures[SKY_DOWN]);
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

    m_displayListSize = GX_EndDispList();
    realloc(m_pDispList, m_displayListSize);
}



void SkyBox::Render()
{
    if ( m_displayListSize > 0 )
	{
        GX_CallDispList(m_pDispList, m_displayListSize);
	}
}


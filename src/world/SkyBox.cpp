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

#include "world/SkyBox.h"
#include "renderer/MasterRenderer.h"
#include "utils/Vector3.h"

#include "SkyBox_Top_png.h"
#include "SkyBox_Left_png.h"
#include "SkyBox_Right_png.h"
#include "SkyBox_Bottom_png.h"
#include "SkyBox_Front_png.h"
#include "SkyBox_Back_png.h"

constexpr uint8_t SKY_FRONT = 0;
constexpr uint8_t SKY_RIGHT = 1;
constexpr uint8_t SKY_LEFT = 2;
constexpr uint8_t SKY_BACK = 3;
constexpr uint8_t SKY_UP = 4;
constexpr uint8_t SKY_DOWN = 5;
constexpr float PLAYER_DISTANCE = 120.0f;
constexpr uint8_t SKYBOX_FACES = 6;

void SkyBox::Init()
{
	m_pSkyBoxTextures[SKY_FRONT] = Texture::Create(SkyBox_Front_png, SkyBox_Front_png_size);
	m_pSkyBoxTextures[SKY_RIGHT] = Texture::Create(SkyBox_Right_png, SkyBox_Right_png_size);
	m_pSkyBoxTextures[SKY_LEFT] = Texture::Create(SkyBox_Left_png, SkyBox_Left_png_size);
	m_pSkyBoxTextures[SKY_BACK] = Texture::Create(SkyBox_Back_png, SkyBox_Back_png_size);
	m_pSkyBoxTextures[SKY_UP] = Texture::Create(SkyBox_Top_png, SkyBox_Top_png_size);
	m_pSkyBoxTextures[SKY_DOWN] = Texture::Create(SkyBox_Bottom_png, SkyBox_Bottom_png_size);

	CreateSkyBox();
}

void SkyBox::Clear()
{
	for (uint8_t i = 0; i < 6; i++)
	{
		delete m_pSkyBoxTextures[i];
		m_pSkyBoxTextures[i] = nullptr;
	}

	m_displayList.Clear();
}

void SkyBox::CreateSkyBox()
{
	m_displayList.Begin(MasterRenderer::GetDisplayListSizeForFaces(SKYBOX_FACES));

	GX_SetCullMode(GX_CULL_BACK);

	m_pSkyBoxTextures[SKY_RIGHT]->Bind();
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(PLAYER_DISTANCE, PLAYER_DISTANCE, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 0);
		GX_Position3f32(PLAYER_DISTANCE, PLAYER_DISTANCE, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 0);
		GX_Position3f32(PLAYER_DISTANCE, 0, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 1);
		GX_Position3f32(PLAYER_DISTANCE, 0, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 1);
	GX_End();

	m_pSkyBoxTextures[SKY_FRONT]->Bind();
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0, PLAYER_DISTANCE, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 0);
		GX_Position3f32(PLAYER_DISTANCE, PLAYER_DISTANCE, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 0);
		GX_Position3f32(PLAYER_DISTANCE, 0, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 1);
		GX_Position3f32(0, 0, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 1);
	GX_End();


	m_pSkyBoxTextures[SKY_UP]->Bind();
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0, PLAYER_DISTANCE, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 0);
		GX_Position3f32(0, PLAYER_DISTANCE, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 0);
		GX_Position3f32(PLAYER_DISTANCE, PLAYER_DISTANCE, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 1);
		GX_Position3f32(PLAYER_DISTANCE, PLAYER_DISTANCE, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 1);
	GX_End();

	GX_SetCullMode(GX_CULL_FRONT);

	m_pSkyBoxTextures[SKY_LEFT]->Bind();
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0, PLAYER_DISTANCE, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 0);
		GX_Position3f32(0, PLAYER_DISTANCE, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 0);
		GX_Position3f32(0, 0, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 1);
		GX_Position3f32(0, 0, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 1);
	GX_End();

	m_pSkyBoxTextures[SKY_BACK]->Bind();
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0, PLAYER_DISTANCE, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 0);
		GX_Position3f32(PLAYER_DISTANCE, PLAYER_DISTANCE, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 0);
		GX_Position3f32(PLAYER_DISTANCE, 0, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 1);
		GX_Position3f32(0, 0, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 1);
	GX_End();

	m_pSkyBoxTextures[SKY_DOWN]->Bind();
	GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
		GX_Position3f32(0, 0, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 1);
		GX_Position3f32(0, 0, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 1);
		GX_Position3f32(PLAYER_DISTANCE, 0, PLAYER_DISTANCE);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(0, 0);
		GX_Position3f32(PLAYER_DISTANCE, 0, 0);
		GX_Color1u32(0xFFFFFFFF);
		GX_TexCoord2f32(1, 0);
	GX_End();

	GX_SetCullMode(GX_CULL_BACK);

	m_displayList.End();
}

void SkyBox::Render()
{
	m_displayList.Render();
}


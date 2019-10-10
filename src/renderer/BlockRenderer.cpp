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

#include "renderer/BlockRenderer.h"
#include "renderer/MasterRenderer.h"

BlockRenderer::BlockRenderer() {}

BlockRenderer::~BlockRenderer() {}


void BlockRenderer::Prepare(std::vector<BlockRenderVO>* positionList, const Block& block)
{
	m_pBlock = &block;
	m_positions = positionList;
	m_renderBlockSize = block.GetSize();
}

void BlockRenderer::Finish()
{
	m_renderBlockSize = 0.0f;
	m_positions = nullptr;
}

void BlockRenderer::Draw()
{
	auto textureMap = m_pBlock->GetTextures();

	for (auto textureIt = textureMap.begin(); textureIt != textureMap.end(); ++textureIt)
	{
		const Texture* pTexture = textureIt->first;
		const std::vector<EBlockFaces>& textureFaces = textureIt->second;

		pTexture->Bind();

		for (auto textureFaceIt = textureFaces.begin(); textureFaceIt != textureFaces.end(); ++textureFaceIt)
		{
			EBlockFaces currentTextureFace = (*textureFaceIt);

			for (auto it = m_positions->begin(); it != m_positions->end(); ++it)
			{
				const Vector3& blockPosition = it->BlockPosition;
				const uint8_t faceMask = it->FaceMask;

				// see http://www.matrix44.net/cms/wp-content/uploads/2011/03/ogl_coord_object_space_cube.png
				guVector vertices[8] =
				{
						{ (float)blockPosition.GetX() - m_renderBlockSize, (float)blockPosition.GetY() + m_renderBlockSize, (float)blockPosition.GetZ() + m_renderBlockSize },// v1
						{ (float)blockPosition.GetX() - m_renderBlockSize, (float)blockPosition.GetY() - m_renderBlockSize, (float)blockPosition.GetZ() + m_renderBlockSize }, //v2
						{ (float)blockPosition.GetX() + m_renderBlockSize, (float)blockPosition.GetY() - m_renderBlockSize, (float)blockPosition.GetZ() + m_renderBlockSize }, //v3
						{ (float)blockPosition.GetX() + m_renderBlockSize, (float)blockPosition.GetY() + m_renderBlockSize, (float)blockPosition.GetZ() + m_renderBlockSize }, // v4
						{ (float)blockPosition.GetX() - m_renderBlockSize, (float)blockPosition.GetY() + m_renderBlockSize, (float)blockPosition.GetZ() - m_renderBlockSize }, //v5
						{ (float)blockPosition.GetX() + m_renderBlockSize, (float)blockPosition.GetY() + m_renderBlockSize, (float)blockPosition.GetZ() - m_renderBlockSize }, // v6
						{ (float)blockPosition.GetX() + m_renderBlockSize, (float)blockPosition.GetY() - m_renderBlockSize, (float)blockPosition.GetZ() - m_renderBlockSize }, // v7
						{ (float)blockPosition.GetX() - m_renderBlockSize, (float)blockPosition.GetY() - m_renderBlockSize, (float)blockPosition.GetZ() - m_renderBlockSize } // v8

				};

				if ((faceMask & FRONT_FACE) && currentTextureFace == EBlockFaces::Front)
				{
					GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
						// front side
						GX_Position3f32(vertices[0].x, vertices[0].y, vertices[0].z);
						GX_Normal3f32(vertices[0].x, vertices[0].y, vertices[0].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 0.0f);
						GX_Position3f32(vertices[3].x, vertices[3].y, vertices[3].z);
						GX_Normal3f32(vertices[3].x, vertices[3].y, vertices[3].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 0.0f);
						GX_Position3f32(vertices[2].x, vertices[2].y, vertices[2].z);
						GX_Normal3f32(vertices[2].x, vertices[2].y, vertices[2].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 1.0f);
						GX_Position3f32(vertices[1].x, vertices[1].y, vertices[1].z);
						GX_Normal3f32(vertices[1].x, vertices[1].y, vertices[1].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 1.0f);
					GX_End();
				}

				if ((faceMask & BACK_FACE) && currentTextureFace == EBlockFaces::Back)
				{
					GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
						// back side
						GX_Position3f32(vertices[5].x, vertices[5].y, vertices[5].z);
						GX_Normal3f32(vertices[5].x, vertices[5].y, vertices[5].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 0.0f);
						GX_Position3f32(vertices[4].x, vertices[4].y, vertices[4].z);
						GX_Normal3f32(vertices[4].x, vertices[4].y, vertices[4].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 0.0f);
						GX_Position3f32(vertices[7].x, vertices[7].y, vertices[7].z);
						GX_Normal3f32(vertices[7].x, vertices[7].y, vertices[7].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 1.0f);
						GX_Position3f32(vertices[6].x, vertices[6].y, vertices[6].z);
						GX_Normal3f32(vertices[6].x, vertices[6].y, vertices[6].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 1.0f);
					GX_End();
				}

				if ((faceMask & RIGHT_FACE) && currentTextureFace == EBlockFaces::Right)
				{
					GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
						// right side
						GX_Position3f32(vertices[3].x, vertices[3].y, vertices[3].z);
						GX_Normal3f32(vertices[3].x, vertices[3].y, vertices[3].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 0.0f);
						GX_Position3f32(vertices[5].x, vertices[5].y, vertices[5].z);
						GX_Normal3f32(vertices[5].x, vertices[5].y, vertices[5].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 0.0f);
						GX_Position3f32(vertices[6].x, vertices[6].y, vertices[6].z);
						GX_Normal3f32(vertices[6].x, vertices[6].y, vertices[6].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 1.0f);
						GX_Position3f32(vertices[2].x, vertices[2].y, vertices[2].z);
						GX_Normal3f32(vertices[2].x, vertices[2].y, vertices[2].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 1.0f);
					GX_End();
				}

				if ((faceMask & LEFT_FACE) && currentTextureFace == EBlockFaces::Left)
				{
					GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
						// left side
						GX_Position3f32(vertices[4].x, vertices[4].y, vertices[4].z);
						GX_Normal3f32(vertices[4].x, vertices[4].y, vertices[4].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 0.0f);
						GX_Position3f32(vertices[0].x, vertices[0].y, vertices[0].z);
						GX_Normal3f32(vertices[0].x, vertices[0].y, vertices[0].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 0.0f);
						GX_Position3f32(vertices[1].x, vertices[1].y, vertices[1].z);
						GX_Normal3f32(vertices[1].x, vertices[1].y, vertices[1].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 1.0f);
						GX_Position3f32(vertices[7].x, vertices[7].y, vertices[7].z);
						GX_Normal3f32(vertices[7].x, vertices[7].y, vertices[7].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 1.0f);
					GX_End();
				}

				if ((faceMask & TOP_FACE) && currentTextureFace == EBlockFaces::Top)
				{
					GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
						// top side
						GX_Position3f32(vertices[4].x, vertices[4].y, vertices[4].z);
						GX_Normal3f32(vertices[4].x, vertices[4].y, vertices[4].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 0.0f);
						GX_Position3f32(vertices[5].x, vertices[5].y, vertices[5].z);
						GX_Normal3f32(vertices[5].x, vertices[5].y, vertices[5].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 0.0f);
						GX_Position3f32(vertices[3].x, vertices[3].y, vertices[3].z);
						GX_Normal3f32(vertices[3].x, vertices[3].y, vertices[3].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 1.0f);
						GX_Position3f32(vertices[0].x, vertices[0].y, vertices[0].z);
						GX_Normal3f32(vertices[0].x, vertices[0].y, vertices[0].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 1.0f);
					GX_End();
				}

				if ((faceMask & BOTTOM_FACE) && currentTextureFace == EBlockFaces::Bottom)
				{
					GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
						// bottom side
						GX_Position3f32(vertices[6].x, vertices[6].y, vertices[6].z);
						GX_Normal3f32(vertices[6].x, vertices[6].y, vertices[6].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 0.0f);
						GX_Position3f32(vertices[7].x, vertices[7].y, vertices[7].z);
						GX_Normal3f32(vertices[7].x, vertices[7].y, vertices[7].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 0.0f);
						GX_Position3f32(vertices[1].x, vertices[1].y, vertices[1].z);
						GX_Normal3f32(vertices[1].x, vertices[1].y, vertices[1].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(1.0f, 1.0f);
						GX_Position3f32(vertices[2].x, vertices[2].y, vertices[2].z);
						GX_Normal3f32(vertices[2].x, vertices[2].y, vertices[2].z);
						GX_Color1u32(0xFFFFFFFF);
						GX_TexCoord2f32(0.0f, 1.0f);
					GX_End();
				}
			}
		}
	}
}

void BlockRenderer::DrawFocusOnSelectedCube(const Vector3& blockWorldPosition, float blockSizeToCenter)
{
	// see http://www.matrix44.net/cms/wp-content/uploads/2011/03/ogl_coord_object_space_cube.png
	guVector vertices[8] =
	{
			{ (float)blockWorldPosition.GetX() - blockSizeToCenter, (float)blockWorldPosition.GetY() + blockSizeToCenter, (float)blockWorldPosition.GetZ() + blockSizeToCenter },// v1
			{ (float)blockWorldPosition.GetX() - blockSizeToCenter, (float)blockWorldPosition.GetY() - blockSizeToCenter, (float)blockWorldPosition.GetZ() + blockSizeToCenter }, //v2
			{ (float)blockWorldPosition.GetX() + blockSizeToCenter, (float)blockWorldPosition.GetY() - blockSizeToCenter, (float)blockWorldPosition.GetZ() + blockSizeToCenter }, //v3
			{ (float)blockWorldPosition.GetX() + blockSizeToCenter, (float)blockWorldPosition.GetY() + blockSizeToCenter, (float)blockWorldPosition.GetZ() + blockSizeToCenter }, // v4
			{ (float)blockWorldPosition.GetX() - blockSizeToCenter, (float)blockWorldPosition.GetY() + blockSizeToCenter, (float)blockWorldPosition.GetZ() - blockSizeToCenter }, //v5
			{ (float)blockWorldPosition.GetX() + blockSizeToCenter, (float)blockWorldPosition.GetY() + blockSizeToCenter, (float)blockWorldPosition.GetZ() - blockSizeToCenter }, // v6
			{ (float)blockWorldPosition.GetX() + blockSizeToCenter, (float)blockWorldPosition.GetY() - blockSizeToCenter, (float)blockWorldPosition.GetZ() - blockSizeToCenter }, // v7
			{ (float)blockWorldPosition.GetX() - blockSizeToCenter, (float)blockWorldPosition.GetY() - blockSizeToCenter, (float)blockWorldPosition.GetZ() - blockSizeToCenter } // v8
	};

	GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 16);
		GX_Position3f32(vertices[1].x, vertices[1].y, vertices[1].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[0].x, vertices[0].y, vertices[0].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[3].x, vertices[3].y, vertices[3].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[2].x, vertices[2].y, vertices[2].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[1].x, vertices[1].y, vertices[1].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[7].x, vertices[7].y, vertices[7].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[6].x, vertices[6].y, vertices[6].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[2].x, vertices[2].y, vertices[2].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[3].x, vertices[3].y, vertices[3].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[5].x, vertices[5].y, vertices[5].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[6].x, vertices[6].y, vertices[6].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[7].x, vertices[7].y, vertices[7].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[4].x, vertices[4].y, vertices[4].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[5].x, vertices[5].y, vertices[5].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[4].x, vertices[4].y, vertices[4].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[0].x, vertices[0].y, vertices[0].z);
		GX_Color1u32(0xFFFFFFFF);
	GX_End();
}

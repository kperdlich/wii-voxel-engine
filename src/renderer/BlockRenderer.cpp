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

#include "BlockRenderer.h"
//#include "MipTexture_tpl.h"

BlockRenderer::BlockRenderer() {}

BlockRenderer::~BlockRenderer() {}


void BlockRenderer::Prepare(std::vector<const BlockRenderVO*> *positionList, float blockSize, const Texture* ptexture)
{
	m_renderBlockSize = blockSize;
	m_positions = positionList;
	if ( ptexture )
	{
		GRRLIB_SetTexture(ptexture->GetNativeTexture(), true, false);
	}
}

void BlockRenderer::Finish()
{
	m_renderBlockSize = 0.0f;
	m_positions = NULL;
}

// note: we start drawing with the top left corner, top right, bottom right, bottom left
void BlockRenderer::Rebuild()
{
	for(auto it = m_positions->begin(); it != m_positions->end(); ++it)
	{
		Vector3 blockPosition = *(*it)->pBlockPosition;
		BlockFaceVisibiltyVO blockRenderVO = *(*it)->pFaceVO;

		// see http://www.matrix44.net/cms/wp-content/uploads/2011/03/ogl_coord_object_space_cube.png
		guVector vertices[8] = {
				{ blockPosition.GetX() - m_renderBlockSize, blockPosition.GetY() + m_renderBlockSize, blockPosition.GetZ() + m_renderBlockSize },// v1
				{ blockPosition.GetX() - m_renderBlockSize, blockPosition.GetY() - m_renderBlockSize, blockPosition.GetZ() + m_renderBlockSize }, //v2
				{ blockPosition.GetX() + m_renderBlockSize, blockPosition.GetY() - m_renderBlockSize, blockPosition.GetZ() + m_renderBlockSize }, //v3
				{ blockPosition.GetX() + m_renderBlockSize, blockPosition.GetY() + m_renderBlockSize, blockPosition.GetZ() + m_renderBlockSize }, // v4
				{ blockPosition.GetX() - m_renderBlockSize, blockPosition.GetY() + m_renderBlockSize, blockPosition.GetZ() - m_renderBlockSize }, //v5
				{ blockPosition.GetX() + m_renderBlockSize, blockPosition.GetY() + m_renderBlockSize, blockPosition.GetZ() - m_renderBlockSize }, // v6
				{ blockPosition.GetX() + m_renderBlockSize, blockPosition.GetY() - m_renderBlockSize, blockPosition.GetZ() - m_renderBlockSize }, // v7
				{ blockPosition.GetX() - m_renderBlockSize, blockPosition.GetY() - m_renderBlockSize, blockPosition.GetZ() - m_renderBlockSize } // v8

		};

		if ( blockRenderVO.bFrontFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// front side
				GX_Position3f32(vertices[0].x, vertices[0].y, vertices[0].z);
				GX_Normal3f32(vertices[0].x, vertices[0].y, vertices[0].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vertices[3].x, vertices[3].y, vertices[3].z);
				GX_Normal3f32(vertices[3].x, vertices[3].y, vertices[3].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vertices[2].x, vertices[2].y, vertices[2].z);
				GX_Normal3f32(vertices[2].x, vertices[2].y, vertices[2].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vertices[1].x, vertices[1].y, vertices[1].z);
				GX_Normal3f32(vertices[1].x, vertices[1].y, vertices[1].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderVO.bBackFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// back side
				GX_Position3f32(vertices[5].x, vertices[5].y, vertices[5].z);
				GX_Normal3f32(vertices[5].x, vertices[5].y, vertices[5].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vertices[4].x, vertices[4].y, vertices[4].z);
				GX_Normal3f32(vertices[4].x, vertices[4].y, vertices[4].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vertices[7].x, vertices[7].y, vertices[7].z);
				GX_Normal3f32(vertices[7].x, vertices[7].y, vertices[7].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vertices[6].x, vertices[6].y, vertices[6].z);
				GX_Normal3f32(vertices[6].x, vertices[6].y, vertices[6].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderVO.bRightFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// right side
				GX_Position3f32(vertices[3].x, vertices[3].y, vertices[3].z);
				GX_Normal3f32(vertices[3].x, vertices[3].y, vertices[3].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vertices[5].x, vertices[5].y, vertices[5].z);
				GX_Normal3f32(vertices[5].x, vertices[5].y, vertices[5].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vertices[6].x, vertices[6].y, vertices[6].z);
				GX_Normal3f32(vertices[6].x, vertices[6].y, vertices[6].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vertices[2].x, vertices[2].y, vertices[2].z);
				GX_Normal3f32(vertices[2].x, vertices[2].y, vertices[2].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderVO.bLeftFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// left side
				GX_Position3f32(vertices[4].x, vertices[4].y, vertices[4].z);
				GX_Normal3f32(vertices[4].x, vertices[4].y, vertices[4].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vertices[0].x, vertices[0].y, vertices[0].z);
				GX_Normal3f32(vertices[0].x, vertices[0].y, vertices[0].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vertices[1].x, vertices[1].y, vertices[1].z);
				GX_Normal3f32(vertices[1].x, vertices[1].y, vertices[1].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vertices[7].x, vertices[7].y, vertices[7].z);
				GX_Normal3f32(vertices[7].x, vertices[7].y, vertices[7].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderVO.bTopFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// top side
				GX_Position3f32(vertices[4].x, vertices[4].y, vertices[4].z);
				GX_Normal3f32(vertices[4].x, vertices[4].y, vertices[4].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vertices[5].x, vertices[5].y, vertices[5].z);
				GX_Normal3f32(vertices[5].x, vertices[5].y, vertices[5].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vertices[3].x, vertices[3].y, vertices[3].z);
				GX_Normal3f32(vertices[3].x, vertices[3].y, vertices[3].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vertices[0].x, vertices[0].y, vertices[0].z);
				GX_Normal3f32(vertices[0].x, vertices[0].y, vertices[0].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderVO.bBottomFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// bottom side
				GX_Position3f32(vertices[6].x, vertices[6].y, vertices[6].z);
				GX_Normal3f32(vertices[6].x, vertices[6].y, vertices[6].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vertices[7].x, vertices[7].y, vertices[7].z);
				GX_Normal3f32(vertices[7].x, vertices[7].y, vertices[7].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vertices[1].x, vertices[1].y, vertices[1].z);
				GX_Normal3f32(vertices[1].x, vertices[1].y, vertices[1].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vertices[2].x, vertices[2].y, vertices[2].z);
				GX_Normal3f32(vertices[2].x, vertices[2].y, vertices[2].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}
	}
}

void BlockRenderer::DrawFocusOnSelectedCube(const Vector3& blockWorldPosition)
{
	// see http://www.matrix44.net/cms/wp-content/uploads/2011/03/ogl_coord_object_space_cube.png
	guVector vertices[8] = {
			{ blockWorldPosition.GetX() - m_renderBlockSize, blockWorldPosition.GetY() + m_renderBlockSize, blockWorldPosition.GetZ() + m_renderBlockSize },// v1
			{ blockWorldPosition.GetX() - m_renderBlockSize, blockWorldPosition.GetY() - m_renderBlockSize, blockWorldPosition.GetZ() + m_renderBlockSize }, //v2
			{ blockWorldPosition.GetX() + m_renderBlockSize, blockWorldPosition.GetY() - m_renderBlockSize, blockWorldPosition.GetZ() + m_renderBlockSize }, //v3
			{ blockWorldPosition.GetX() + m_renderBlockSize, blockWorldPosition.GetY() + m_renderBlockSize, blockWorldPosition.GetZ() + m_renderBlockSize }, // v4
			{ blockWorldPosition.GetX() - m_renderBlockSize, blockWorldPosition.GetY() + m_renderBlockSize, blockWorldPosition.GetZ() - m_renderBlockSize }, //v5
			{ blockWorldPosition.GetX() + m_renderBlockSize, blockWorldPosition.GetY() + m_renderBlockSize, blockWorldPosition.GetZ() - m_renderBlockSize }, // v6
			{ blockWorldPosition.GetX() + m_renderBlockSize, blockWorldPosition.GetY() - m_renderBlockSize, blockWorldPosition.GetZ() - m_renderBlockSize }, // v7
			{ blockWorldPosition.GetX() - m_renderBlockSize, blockWorldPosition.GetY() - m_renderBlockSize, blockWorldPosition.GetZ() - m_renderBlockSize } // v8

	};

	GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 16);
		GX_Position3f32(vertices[1].x,vertices[1].y,vertices[1].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[0].x,vertices[0].y,vertices[0].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[3].x,vertices[3].y,vertices[3].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[2].x,vertices[2].y,vertices[2].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[1].x,vertices[1].y,vertices[1].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[7].x,vertices[7].y,vertices[7].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[6].x,vertices[6].y,vertices[6].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[2].x,vertices[2].y,vertices[2].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[3].x,vertices[3].y,vertices[3].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[5].x,vertices[5].y,vertices[5].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[6].x,vertices[6].y,vertices[6].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[7].x,vertices[7].y,vertices[7].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[4].x,vertices[4].y,vertices[4].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[5].x,vertices[5].y,vertices[5].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[4].x,vertices[4].y,vertices[4].z);
		GX_Color1u32(0xFFFFFFFF);
		GX_Position3f32(vertices[0].x,vertices[0].y,vertices[0].z);
		GX_Color1u32(0xFFFFFFFF);
	GX_End();
}

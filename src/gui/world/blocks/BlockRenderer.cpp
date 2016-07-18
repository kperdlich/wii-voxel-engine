/*
 * BlockRenderer.cpp
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#include "BlockRenderer.h"
//#include "MipTexture_tpl.h"

BlockRenderer::BlockRenderer( )
{

}

BlockRenderer::~BlockRenderer() {

}


void BlockRenderer::Prepare(std::vector<BlockRenderData*> *positionList, float blockSize, Texture* ptexture)
{
	m_renderBlockSize = blockSize;
	m_positions = positionList;
	GRRLIB_SetTexture(ptexture->getNativeTexture(), true, false);
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
		Vector3f blockPosition = *(*it)->BlockPosition;
		BlockFaceVisibiltyData blockRenderData = *(*it)->FaceData;

		// see http://www.matrix44.net/cms/wp-content/uploads/2011/03/ogl_coord_object_space_cube.png
		guVector vbo[8] = {
				{ blockPosition.GetX() - m_renderBlockSize, blockPosition.GetY() + m_renderBlockSize, blockPosition.GetZ() + m_renderBlockSize },// v1
				{ blockPosition.GetX() - m_renderBlockSize, blockPosition.GetY() - m_renderBlockSize, blockPosition.GetZ() + m_renderBlockSize }, //v2
				{ blockPosition.GetX() + m_renderBlockSize, blockPosition.GetY() - m_renderBlockSize, blockPosition.GetZ() + m_renderBlockSize }, //v3
				{ blockPosition.GetX() + m_renderBlockSize, blockPosition.GetY() + m_renderBlockSize, blockPosition.GetZ() + m_renderBlockSize }, // v4
				{ blockPosition.GetX() - m_renderBlockSize, blockPosition.GetY() + m_renderBlockSize, blockPosition.GetZ() - m_renderBlockSize }, //v5
				{ blockPosition.GetX() + m_renderBlockSize, blockPosition.GetY() + m_renderBlockSize, blockPosition.GetZ() - m_renderBlockSize }, // v6
				{ blockPosition.GetX() + m_renderBlockSize, blockPosition.GetY() - m_renderBlockSize, blockPosition.GetZ() - m_renderBlockSize }, // v7
				{ blockPosition.GetX() - m_renderBlockSize, blockPosition.GetY() - m_renderBlockSize, blockPosition.GetZ() - m_renderBlockSize } // v8

		};

		if ( blockRenderData.FrontFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// front side
				GX_Position3f32(vbo[0].x, vbo[0].y, vbo[0].z);
				GX_Normal3f32(vbo[0].x, vbo[0].y, vbo[0].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vbo[3].x, vbo[3].y, vbo[3].z);
				GX_Normal3f32(vbo[3].x, vbo[3].y, vbo[3].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vbo[2].x, vbo[2].y, vbo[2].z);
				GX_Normal3f32(vbo[2].x, vbo[2].y, vbo[2].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vbo[1].x, vbo[1].y, vbo[1].z);
				GX_Normal3f32(vbo[1].x, vbo[1].y, vbo[1].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderData.BackFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// back side
				GX_Position3f32(vbo[5].x, vbo[5].y, vbo[5].z);
				GX_Normal3f32(vbo[5].x, vbo[5].y, vbo[5].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vbo[4].x, vbo[4].y, vbo[4].z);
				GX_Normal3f32(vbo[4].x, vbo[4].y, vbo[4].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vbo[7].x, vbo[7].y, vbo[7].z);
				GX_Normal3f32(vbo[7].x, vbo[7].y, vbo[7].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vbo[6].x, vbo[6].y, vbo[6].z);
				GX_Normal3f32(vbo[6].x, vbo[6].y, vbo[6].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderData.RightFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// right side
				GX_Position3f32(vbo[3].x, vbo[3].y, vbo[3].z);
				GX_Normal3f32(vbo[3].x, vbo[3].y, vbo[3].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vbo[5].x, vbo[5].y, vbo[5].z);
				GX_Normal3f32(vbo[5].x, vbo[5].y, vbo[5].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vbo[6].x, vbo[6].y, vbo[6].z);
				GX_Normal3f32(vbo[6].x, vbo[6].y, vbo[6].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vbo[2].x, vbo[2].y, vbo[2].z);
				GX_Normal3f32(vbo[2].x, vbo[2].y, vbo[2].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderData.LeftFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// left side
				GX_Position3f32(vbo[4].x, vbo[4].y, vbo[4].z);
				GX_Normal3f32(vbo[4].x, vbo[4].y, vbo[4].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vbo[0].x, vbo[0].y, vbo[0].z);
				GX_Normal3f32(vbo[0].x, vbo[0].y, vbo[0].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vbo[1].x, vbo[1].y, vbo[1].z);
				GX_Normal3f32(vbo[1].x, vbo[1].y, vbo[1].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vbo[7].x, vbo[7].y, vbo[7].z);
				GX_Normal3f32(vbo[7].x, vbo[7].y, vbo[7].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderData.TopFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// top side
				GX_Position3f32(vbo[4].x, vbo[4].y, vbo[4].z);
				GX_Normal3f32(vbo[4].x, vbo[4].y, vbo[4].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vbo[5].x, vbo[5].y, vbo[5].z);
				GX_Normal3f32(vbo[5].x, vbo[5].y, vbo[5].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vbo[3].x, vbo[3].y, vbo[3].z);
				GX_Normal3f32(vbo[3].x, vbo[3].y, vbo[3].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vbo[0].x, vbo[0].y, vbo[0].z);
				GX_Normal3f32(vbo[0].x, vbo[0].y, vbo[0].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}

		if ( blockRenderData.BottomFace )
		{
			GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
				// bottom side
				GX_Position3f32(vbo[6].x, vbo[6].y, vbo[6].z);
				GX_Normal3f32(vbo[6].x, vbo[6].y, vbo[6].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,0.0f);
				GX_Position3f32(vbo[7].x, vbo[7].y, vbo[7].z);
				GX_Normal3f32(vbo[7].x, vbo[7].y, vbo[7].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,0.0f);
				GX_Position3f32(vbo[1].x, vbo[1].y, vbo[1].z);
				GX_Normal3f32(vbo[1].x, vbo[1].y, vbo[1].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(1.0f,1.0f);
				GX_Position3f32(vbo[2].x, vbo[2].y, vbo[2].z);
				GX_Normal3f32(vbo[2].x, vbo[2].y, vbo[2].z);
				GX_Color1u32(0xFFFFFFFF);
				GX_TexCoord2f32(0.0f,1.0f);
			GX_End();
		}
	}
}

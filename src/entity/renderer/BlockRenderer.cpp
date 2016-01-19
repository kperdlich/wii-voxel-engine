/*
 * BlockRenderer.cpp
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#include "BlockRenderer.h"
#include "GroundText_png.h"
#include "../Block.h"

BlockRenderer::BlockRenderer( Entity* entity ) : EntityRenderer( entity )
{
	this->setTexture(getTextureHandler()->createTexture( GroundText_png ));
}

BlockRenderer::~BlockRenderer() {

}


// note: we start drawing with the top left corner, top right, bottom right, bottom left
void BlockRenderer::render()
{
	CBlock* pBlockToRender = static_cast<CBlock*>(m_Entity);
	Vector3f blockPosition = pBlockToRender->getPosition();
	float blockSize = pBlockToRender->getSize();

	// see http://www.matrix44.net/cms/wp-content/uploads/2011/03/ogl_coord_object_space_cube.png
	guVector vbo[8] = {
			{ blockPosition.getX() - blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() + blockSize },// v1
			{ blockPosition.getX() - blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() + blockSize }, //v2
			{ blockPosition.getX() + blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() + blockSize }, //v3
			{ blockPosition.getX() + blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() + blockSize }, // v4
			{ blockPosition.getX() - blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() - blockSize }, //v5
			{ blockPosition.getX() + blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() - blockSize }, // v6
			{ blockPosition.getX() + blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() - blockSize }, // v7
			{ blockPosition.getX() - blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() - blockSize } // v8

	};

	GRRLIB_SetTexture(m_entityTexture->getNativeTexture(), 1);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
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

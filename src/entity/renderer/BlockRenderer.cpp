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
	//GRRLIB_DrawTessPanel(6.2f,0.17f,3.7f,0.1f,0,0xFFFFFFFF);

	CBlock* pBlockToRender = static_cast<CBlock*>(m_Entity);
	Vector3f blockPosition = pBlockToRender->getPosition();
	float blockSize = pBlockToRender->getSize();

	GRRLIB_SetTexture(m_entityTexture->getNativeTexture(), 0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
			// front side
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			// back side
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			// right side
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			// left side
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			// top side
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() + blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			// bottom side
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() - blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(blockPosition.getX() - blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(blockPosition.getX() + blockSize, blockPosition.getY() - blockSize, blockPosition.getZ() + blockSize);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);
		GX_End();
}

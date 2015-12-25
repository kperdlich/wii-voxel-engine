/*
 * BlockRenderer.cpp
 *
 *  Created on: 10.07.2015
 *      Author: Kevin
 */

#include "BlockRenderer.h"
#include "GroundText_png.h"

BlockRenderer::BlockRenderer( Entity* entity ) : EntityRenderer( entity )
{
	this->setTexture(getTextureHandler()->createTexture( GroundText_png ));
}

BlockRenderer::~BlockRenderer() {

}

void BlockRenderer::render()
{
	//GRRLIB_DrawTessPanel(6.2f,0.17f,3.7f,0.1f,0,0xFFFFFFFF);

	GRRLIB_SetTexture(m_entityTexture->getNativeTexture(), 0);
	GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
			GX_Position3f32(-1.0f,1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(1.0f,1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(1.0f,-1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(-1.0f,-1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			GX_Position3f32(1.0f,1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(-1.0f,1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(-1.0f,-1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(1.0f,-1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			GX_Position3f32(1.0f,1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(1.0f,1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(1.0f,-1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(1.0f,-1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			GX_Position3f32(-1.0f,1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(-1.0f,1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(-1.0f,-1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(-1.0f,-1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			GX_Position3f32(-1.0f,1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(1.0f,1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(1.0f,1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(-1.0f,1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);

			GX_Position3f32(1.0f,-1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,0.0f);
			GX_Position3f32(-1.0f,-1.0f,-1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,0.0f);
			GX_Position3f32(-1.0f,-1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(1.0f,1.0f);
			GX_Position3f32(1.0f,-1.0f,1.0f);
			GX_Color1u32(0xFFFFFFFF);
			GX_TexCoord2f32(0.0f,1.0f);
		GX_End();
}

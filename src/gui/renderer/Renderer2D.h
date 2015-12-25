/*
 * Renderer2D.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_RENDERER_RENDERER2D_H_
#define SRC_GUI_RENDERER_RENDERER2D_H_

#include "Renderer.h"
#include "../Texture.h"
#include "../SpriteSheet.h"
#include "../LabelTexture.h"

class Renderer2D : public Renderer {

public:
	Renderer2D();
	~Renderer2D();
	void drawTexture( Texture* texture, const f32 xpos, const f32 ypos, const f32 degrees, const f32 scaleX, const f32 scaleY, const f32 color );
	void drawTexture( Texture* texture, const f32 xpos, const f32 ypos );
	void drawTexture( BasicTexture* basicTexture );
	void drawTile(SpriteSheet* tilemap, const f32 xpos, const f32 ypos, const f32 degrees, const f32 scaleX, const f32 scaleY,
					const u32 color, const int frame);
};

#endif /* SRC_GUI_RENDERER_RENDERER2D_H_ */

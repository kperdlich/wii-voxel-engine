/*
 * Renderer2D.h
 *
 *  Created on: 24.05.2015
 *      Author: Kevin
 */

#ifndef _RENDERER2D_H_
#define _RENDERER2D_H_

#include "Renderer.h"
#include "../textures/Texture.h"
#include "../textures/SpriteSheet.h"
#include "../textures/LabelTexture.h"
#include "../textures/Tile.h"

class Renderer2D : public Renderer {

public:
	Renderer2D();
	~Renderer2D();
	void DrawTexture( const Texture* texture, const f32 xpos, const f32 ypos, const f32 degrees, const f32 scaleX, const f32 scaleY, const f32 color );
	void DrawTexture( const Texture* texture, const f32 xpos, const f32 ypos );
	void DrawTexture( const BasicTexture& basicTexture );
	void DrawTile(const SpriteSheet* tilemap, const f32 xpos, const f32 ypos, const f32 degrees, const f32 scaleX, const f32 scaleY,
					const u32 color, const int frame);
};

#endif /* _RENDERER2D_H_ */

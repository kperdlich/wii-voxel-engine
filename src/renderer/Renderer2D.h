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

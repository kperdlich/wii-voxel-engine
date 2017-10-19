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
#include "../textures/LabelSprite.h"

class Renderer2D : public Renderer {

public:
	Renderer2D();
	~Renderer2D();
    void Draw( const Sprite* texture, const f32 xpos, const f32 ypos, const f32 degrees, const f32 scaleX, const f32 scaleY, const f32 color );
    void Draw( const Sprite* texture, const f32 xpos, const f32 ypos );
    void Draw( const Sprite& sprite);
};

#endif /* _RENDERER2D_H_ */

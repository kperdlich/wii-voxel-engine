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

#include "Renderer2D.h"
#include "MasterRenderer.h"

void Renderer2D::Draw(const Sprite* sprite, const f32 xpos, const f32 ypos,
		const f32 degrees, const f32 scaleX, const f32 scaleY,
		const f32 color)
{
    MasterRenderer::DrawSprite(*sprite, xpos , ypos, degrees, scaleX, scaleY, color);
}

void Renderer2D::Draw(const Sprite* sprite, const f32 xpos, const f32 ypos) {
    MasterRenderer::DrawSprite(*sprite, xpos, ypos, 0, 1, 1, GRRLIB_WHITE );
}

Renderer2D::Renderer2D() {

}

Renderer2D::~Renderer2D() {
}

void Renderer2D::Draw(const Sprite& sprite)
{
    switch( sprite.GetTextureType() )
	{
		case SPRITE:
		{            
            MasterRenderer::DrawSprite(sprite, sprite.GetX(), sprite.GetY(), 0, 1, 1, sprite.GetColor() );
			break;
		}	
		case LABEL:
		{
            Label label = static_cast<const Label&>(sprite);
			GRRLIB_PrintfTTF( label.GetX(), label.GetY(), &label.GetFont(), label.GetText(), label.GetFontSize(), label.GetTextColor() );
			break;
		}
		default:
			break;
	}
}





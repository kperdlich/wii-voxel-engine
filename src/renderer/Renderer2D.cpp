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

void Renderer2D::DrawTexture(const Texture* texture, const f32 xpos, const f32 ypos,
		const f32 degrees, const f32 scaleX, const f32 scaleY,
		const f32 color)
{
	GRRLIB_DrawImg( xpos , ypos, texture->GetNativeTexture(), degrees, scaleX, scaleY, color);
}

void Renderer2D::DrawTexture(const Texture* texture, const f32 xpos, const f32 ypos) {
	GRRLIB_DrawImg( xpos, ypos, texture->GetNativeTexture(), 0, 1, 1, GRRLIB_WHITE );
}

Renderer2D::Renderer2D() {

}

Renderer2D::~Renderer2D() {
}

void Renderer2D::DrawTexture(const BasicTexture& basicTexture)
{
	switch( basicTexture.GetTextureType() )
	{
		case SPRITE:
		{
			Texture tx = static_cast<const Texture&>(basicTexture);
			GRRLIB_DrawImg( tx.GetX(), tx.GetY(), tx.GetNativeTexture(), 0, 1, 1, tx.GetColor() );
			break;
		}
		case TILE:
		{
			Tile ti = static_cast<const Tile&>( basicTexture);
			GRRLIB_DrawTile(ti.GetX(), ti.GetY(), ti.getSpriteSheet()->GetNativeTexture(), 0, 1, 1, GRRLIB_WHITE, ti.getSheetIndex());
			break;
		}
		case LABEL:
		{
			LabelTexture label = static_cast<const LabelTexture&>(basicTexture);
			GRRLIB_PrintfTTF( label.GetX(), label.GetY(), &label.getFont(), label.getText(), label.getFontSize(), label.getTextColor() );
			break;
		}
		default:
			break;
	}
}

void Renderer2D::DrawTile(const SpriteSheet* tilemap, const f32 xpos, const f32 ypos,
		const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color,
		const int frame)
{
	GRRLIB_DrawTile(xpos, ypos, tilemap->GetNativeTexture(), degrees, scaleX, scaleY, color, frame);
}




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

#include "Renderer.h"
#include "MasterRenderer.h"
#include "../textures/Sprite.h"
#include "../textures/Label.h"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Draw(const ISprite& sprite)
{
    switch( sprite.GetType() )
    {
        case ESpriteType::SPRITE:
        {
            MasterRenderer::DrawSprite(static_cast<const Sprite&>(sprite));
            break;
        }
        case ESpriteType::LABEL:
        {
            auto& label = static_cast<const Label&>(sprite);
            GRRLIB_PrintfTTF( label.GetX(), label.GetY(), &label.GetFont(), label.GetText().c_str(), label.GetFontSize(), label.GetTextColor() );
            break;
        }
        default:
            break;
    }
}


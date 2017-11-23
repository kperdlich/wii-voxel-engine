/***
 *
 * Copyright (C) 2017 DaeFennek
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

#include "Sprite.h"
#include "../Engine.h"
#include "../renderer/MasterRenderer.h"

Sprite::Sprite(float x, float y, TextureLoadingData textureData) : BasicTexture(x, y, textureData), m_bVisible(true) { }

Sprite::~Sprite()
{
    Engine::Get().GetSpriteStageManager().Remove(*this);
}

Sprite* Sprite::Create(const uint8_t *spriteData, uint32_t spriteSize, std::string searchName, uint16_t sortingLayer)
{
    TextureLoadingData spriteLoadingData = { spriteData, spriteSize };
    auto sprite = new Sprite( 0, 0, spriteLoadingData );
    sprite->SetName(searchName);
    sprite->SetSortingLayerIndex(sortingLayer);
    sprite->Load();
    Engine::Get().GetSpriteStageManager().Add(sprite);
    return sprite;
}

void Sprite::Render() const
{
    MasterRenderer::DrawSprite(*this);
}

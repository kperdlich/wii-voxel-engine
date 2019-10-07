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

#pragma once

#include <string>
#include "textures/BasicTexture.h"
#include "textures/ISprite.h"

class Sprite : public BasicTexture, public ISprite
{
protected:
    Sprite( float x, float y, TextureLoadingData textureData );

public:    
    ~Sprite();

    static Sprite* Create(const uint8_t *pSpriteData, uint32_t spriteSize, std::string searchName, uint16_t sortingLayer = 0);

    void Render() const override;

    ESpriteType GetType() const override
    {
        return ESpriteType::SPRITE;
    }

    bool IsVisible() const override
    {
        return m_bVisible && m_bTextureLoaded;
    }

    void SetVisible(bool value) override
    {
        m_bVisible = value;
    }

    void SetSortingLayerIndex(uint16_t index) override
    {
        m_sortingLayerIndex = index;
    }

    uint16_t GetSortingLayerIndex() const override
    {
        return m_sortingLayerIndex;
    }

    const std::string& GetName() const override
    {
        return m_name;
    }

    void SetName(const std::string& name) override
    {
        m_name = name;
    }

protected:
    std::string m_name;
    bool m_bVisible = true;
    uint16_t m_sortingLayerIndex = 0;
};

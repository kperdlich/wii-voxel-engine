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

#ifndef SPRITE_H
#define SPRITE_H

#include "BasicTexture.h"

class Sprite : public BasicTexture
{
public:
    Sprite( float x, float y, TextureLoadingData textureData, const uint16_t id ) : BasicTexture(x, y, textureData, id), m_bVisible(true) {}
    ~Sprite(){}

    virtual ETextureType GetTextureType() const override
    {
        return SPRITE;
    }

    virtual bool IsVisible() const
    {
        return m_bVisible && m_bTextureLoaded;
    }

    virtual void SetVisible(bool value)
    {
        m_bVisible = value;
    }

    void SetSortingLayerIndex(uint16_t index)
    {
        m_sortingLayerIndex = index;
    }

    uint16_t GetSortingLayerIndex()
    {
        return m_sortingLayerIndex;
    }

    bool operator > (const Sprite& sprite) const
    {
        return (m_sortingLayerIndex > sprite.m_sortingLayerIndex);
    }

    bool operator < (const Sprite& sprite) const
    {
        return (m_sortingLayerIndex < sprite.m_sortingLayerIndex);
    }

protected:
    bool m_bVisible = true;
    uint16_t m_sortingLayerIndex = 0;
};




#endif // SPRITE_H

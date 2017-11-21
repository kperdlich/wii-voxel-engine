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

#ifndef _BASICTEXTURE_H_
#define _BASICTEXTURE_H_

#include "IDrawable.h"
#include "../core/grrlib.h"
#include "../utils/ColorHelper.h"

typedef struct
{
    const uint8_t* textureData;
    uint32_t textureSize;
} TextureLoadingData;

class BasicTexture : public IDrawable {
public:
    BasicTexture(float x, float y, TextureLoadingData textureData);
    virtual ~BasicTexture();

    virtual void Load();
    virtual void Unload();

    float GetX() const override
    {
        return m_x;
    }

    void SetX(float x) override
    {
        m_x = x;
    }

    float GetY() const override
    {
        return m_y;
    }

    void SetY(float y) override
    {
        m_y = y;
    }

    void SetColor(uint32_t color)
    {
        m_color = color;
    }

    uint32_t GetColor() const
    {
        return m_color;
    }

    virtual uint32_t GetWidth() const
    {
        return m_width;
    }

    virtual uint32_t GetHeight() const
    {
        return m_height;
    }

    bool IsLoaded() const
    {
        return m_bTextureLoaded;
    }   

    /**
     * @brief GetLoadedTexture
     * @return Returns null if the texture is not loaded otherwise loading informations depending on the TextureLoadingData
     */
    void* GetLoadedTexture() const
    {
        return m_loadedTexture;
    }

    /**
     * @brief GetTextureObject
     * @return Returns null if texture not loaded otherwise a pointer to the initalized GXTexObj
     */
    GXTexObj* GetTextureObject() const
    {
        return m_textureObject;
    }

    float GetScaleX() const
    {
        return m_scaleX;
    }

    void SetScaleX(float scaleX)
    {
        m_scaleX = scaleX;
    }

    float GetScaleY() const
    {
        return m_scaleY;
    }

    void SetScaleY(float scaleY)
    {
        m_scaleX = scaleY;
    }

protected:
    float m_x, m_y;
    float m_width, m_height;
    float m_scaleX = 1.0f, m_scaleY = 1.0f;
    uint32_t m_color;
    TextureLoadingData m_textureLoadingData;
    bool m_bTextureLoaded = false;
    void* m_loadedTexture = nullptr;
    GXTexObj* m_textureObject = nullptr;
};

#endif /* _BASICTEXTURE_H_ */

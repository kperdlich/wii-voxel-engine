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

#include "../core/grrlib.h"
#include "../utils/ColorHelper.h"

enum ETextureType {
	INVALID,
    TEXTURE,
	SPRITE,
	SPRITE_SHEET,
	TILE,
	LABEL
};

typedef struct
{
    const uint8_t* pTextureData;
    uint32_t textureSize;
} TextureLoadingData;

class BasicTexture {
public:
    BasicTexture(float x, float y, TextureLoadingData textureData, uint16_t id) : m_x(x), m_y(y), m_textureLoadingData(textureData), m_id(id), m_color(GRRLIB_WHITE) {}
    virtual ~BasicTexture() {}

    virtual void Load();
    virtual void Unload();

    float GetX() const
    {
        return m_x;
    }

    void SetX(float x)
    {
        m_x = x;
    }

    float GetY() const
    {
        return m_y;
    }

    void SetY(float y)
    {
        m_y = y;
    }

    virtual ETextureType GetTextureType() const
    {
        return INVALID;
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

    uint16_t GetId() const
    {
        return m_id;
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
        return m_pTextureObject;
    }

protected:
	float m_x, m_y;
    float m_width, m_height;
    const uint16_t m_id;	
    uint32_t m_color;
    TextureLoadingData m_textureLoadingData;
    bool m_bTextureLoaded = false;
    void* m_loadedTexture = nullptr;
    GXTexObj* m_pTextureObject = nullptr;
};

#endif /* _BASICTEXTURE_H_ */

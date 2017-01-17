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

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../core/grrlib.h"
#include "BasicTexture.h"
#include <ogc/gx.h>

typedef struct
{
    const uint8_t* pTextureData;
    uint32_t textureSize;
} TextureData;

class Texture : public BasicTexture
{

protected:
    TextureData m_textureData;
    GRRLIB_texImg* m_pGrrlibTexture = nullptr;
    bool m_bTextureLoaded;

    void* m_pTplTextureData = nullptr;
    GXTexObj* m_pTextureObject = nullptr;

public:
    Texture( float x, float y, const TextureData& textureData, const uint16_t id );
	virtual ~Texture();

	virtual ETextureType GetTextureType() const override;

    GRRLIB_texImg* GetGrrlibTexture() const;

    GXTexObj* GetTextureObject() const
    {
        return m_pTextureObject;
    }

	virtual void LoadTexture() override;
    virtual void UnloadTexture() override;

    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;

    bool IsLoaded() const;
	virtual bool IsVisible() const override;

    void PrintTlpInfo();

private:
    void LoadTplTexture();
    void LoadDefaultTexture();
    bool IsTplTexture();

};


#endif /* _TEXTURE_H_ */

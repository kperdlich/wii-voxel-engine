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


class Texture : public BasicTexture
{

protected:
    const unsigned char* m_pTextureBytes = nullptr;
    GRRLIB_texImg* m_pTexture = nullptr;
    bool m_bTextureLoaded;

    GXTexObj* m_pTextureObject = nullptr;

public:
    Texture( float x, float y, const unsigned char* texture, const uint16_t id );
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
};


#endif /* _TEXTURE_H_ */

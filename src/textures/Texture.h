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

public:
    Texture(float x, float y, TextureLoadingData textureData) : BasicTexture(x, y, textureData) {}
    virtual ~Texture() {}

    virtual void Load() override;
    virtual void Unload() override;

    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;	

    void PrintTPLInfo();

    virtual ETextureType GetTextureType() const override
    {
        return TEXTURE;
    }

protected:
    void* m_pTPLTextureData = nullptr;

private:

    void LoadTPLTexture();
    bool IsTPLTexture();

};


#endif /* _TEXTURE_H_ */

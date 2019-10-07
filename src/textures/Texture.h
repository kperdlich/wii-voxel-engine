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

#pragma once

#include <gccore.h>
#include "core/grrlib.h"
#include "textures/BasicTexture.h"

class Texture : public BasicTexture
{
protected:
    Texture(float x, float y, TextureLoadingData textureData) : BasicTexture(x, y, textureData) {}

public:    
    ~Texture() override {}

    void Load() override;
    void Unload() override;

    static Texture* Create(const uint8_t* textureData, uint32_t textureSize);

    void Bind(uint8_t textureMapSlot = GX_TEXMAP0) const;

    uint32_t GetWidth() const override;
    uint32_t GetHeight() const override;
protected:
    void* m_pTPLTextureData = nullptr;

private:
    void LoadTPLTexture();
    bool IsTPLTexture();

};

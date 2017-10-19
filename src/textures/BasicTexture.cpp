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

#include "BasicTexture.h"

void BasicTexture::Load()
{
    m_loadedTexture = GRRLIB_LoadTexture( m_textureLoadingData.pTextureData );

    if ( m_loadedTexture )
    {        
        m_pTextureObject = new GXTexObj();
        auto pLoadedTextureInfo = static_cast<GRRLIB_texImg*>(m_loadedTexture);

        GX_InitTexObj(m_pTextureObject, pLoadedTextureInfo->data, pLoadedTextureInfo->w, pLoadedTextureInfo->h, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

        GX_InitTexObjLOD(m_pTextureObject, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);

        if (GRRLIB_Settings.antialias == false)
        {
            GX_SetCopyFilter(GX_FALSE, rmode->sample_pattern, GX_FALSE, rmode->vfilter);
        }
        else
        {
            GX_SetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);
        }

        m_width = pLoadedTextureInfo->w;
        m_height = pLoadedTextureInfo->h;
        m_bTextureLoaded = true;
    }
}

void BasicTexture::Unload()
{
    if ( m_loadedTexture )
    {
        GRRLIB_FreeTexture(static_cast<GRRLIB_texImg*>(m_loadedTexture));
    }

    if (m_pTextureObject)
    {
        delete m_pTextureObject;
    }

    m_width = 0;
    m_height = 0;
    m_bTextureLoaded = false;
}

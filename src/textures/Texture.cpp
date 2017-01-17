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


#include "Texture.h"


Texture::Texture(float x, float y, const unsigned char* texture, const u16 id ) : m_pTextureBytes(texture), BasicTexture(x, y, id)
{
    m_pTexture = nullptr;
    m_bVisible = true;
}

Texture::~Texture()
{

}

GRRLIB_texImg* Texture::GetGrrlibTexture() const
{
    return this->m_pTexture;
}

void Texture::LoadTexture()
{
    UnloadTexture();

    m_pTexture = GRRLIB_LoadTexture( m_pTextureBytes );

    if ( m_pTexture )
    {
        m_pTextureObject = new GXTexObj();

        GX_InitTexObj(m_pTextureObject, m_pTexture->data, m_pTexture->w, m_pTexture->h, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_FALSE);

        GX_InitTexObjLOD(m_pTextureObject, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);

        if (GRRLIB_Settings.antialias == false)
        {

            GX_SetCopyFilter(GX_FALSE, rmode->sample_pattern, GX_FALSE, rmode->vfilter);
        }
        else
        {
            GX_SetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);
        }

        m_bTextureLoaded = true;
    }
}

void Texture::UnloadTexture()
{

    if ( m_pTexture )
	{
        GRRLIB_FreeTexture( m_pTexture );
	}

    if ( m_pTextureObject )
    {
        delete m_pTextureObject;
    }

    m_bTextureLoaded = false;
}

uint32_t Texture::GetWidth() const
{

    if ( m_bTextureLoaded )
	{
        return m_pTexture->w;
	}
	return 0;
}

uint32_t Texture::GetHeight() const
{

    if ( m_bTextureLoaded )
	{
        return m_pTexture->h;
	}
	return 0;
}

bool Texture::IsVisible() const
{
    return m_bVisible && m_bTextureLoaded;
}

ETextureType Texture::GetTextureType() const
{
	return SPRITE;
}

bool Texture::IsLoaded() const
{
    return m_bTextureLoaded;
}

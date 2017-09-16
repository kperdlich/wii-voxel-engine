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

typedef struct {
    uint32_t	magic;
    uint32_t	texCount;
    uint32_t	headerSize;
} TPL_Header;

typedef struct {
    uint32_t	textureOffs;
    uint32_t	tlutOffs;
} TPL_Addr;

typedef struct {
    uint16_t	height;
    uint16_t	width;
    uint32_t	format;
    uint32_t	dataOffs;
    uint32_t	wrap_s;
    uint32_t	wrap_t;
    uint32_t	minFilt;
    uint32_t	magFilt;
    float	lodBias;
    uint8_t	edgeLod;
    uint8_t	minLod;
    uint8_t	maxLod;
    uint8_t	unpacked;
} TPL_Texture;

Texture::Texture(float x, float y, TextureData textureData, const uint16_t id ) : BasicTexture(x, y, id), m_textureData(textureData)
{
    m_pGrrlibTexture = nullptr;
    m_bVisible = true;
}

Texture::~Texture()
{

}

GRRLIB_texImg* Texture::GetGrrlibTexture() const
{
    return this->m_pGrrlibTexture;
}

void Texture::LoadTplTexture()
{
    //const TPL_Header* pHeader = reinterpret_cast<const TPL_Header*>(m_textureData.pTextureData);
    //const TPL_Addr* pAddr =reinterpret_cast<const TPL_Addr*>((m_textureData.pTextureData + sizeof(TPL_Header)));
    const TPL_Texture* pTexture = reinterpret_cast<const TPL_Texture*>((m_textureData.pTextureData + sizeof(TPL_Header) + sizeof(TPL_Addr)));

    uint32_t size = m_textureData.textureSize - sizeof(TPL_Header) - sizeof(TPL_Addr) - sizeof(TPL_Texture);
    m_pTplTextureData = memalign(32, size);
    memcpy(m_pTplTextureData, (void*) (m_textureData.pTextureData + pTexture->dataOffs), size);

    DCFlushRange(m_pTplTextureData, size);

    GX_InitTexObj(m_pTextureObject, m_pTplTextureData, pTexture->width, pTexture->height, pTexture->format, pTexture->wrap_s, pTexture->wrap_t, GX_FALSE);

    if (pTexture->maxLod)
    {
        GX_InitTexObjLOD(m_pTextureObject, pTexture->minFilt, pTexture->magFilt, pTexture->minLod, pTexture->maxLod, pTexture->lodBias, GX_DISABLE, pTexture->edgeLod, GX_ANISO_4);

        GX_InitTexObjEdgeLOD(m_pTextureObject, GX_ENABLE);
        GX_InitTexObjMaxAniso(m_pTextureObject, GX_ANISO_4);
    }
    else
    {
        GX_InitTexObjFilterMode(m_pTextureObject, pTexture->minFilt, pTexture->magFilt);
    }

    m_bTextureLoaded = true;
}

void Texture::LoadDefaultTexture()
{
    m_pGrrlibTexture = GRRLIB_LoadTexture( m_textureData.pTextureData );

    if ( m_pGrrlibTexture )
    {
        GX_InitTexObj(m_pTextureObject, m_pGrrlibTexture->data, m_pGrrlibTexture->w, m_pGrrlibTexture->h, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

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

bool Texture::IsTplTexture()
{
    const TPL_Header* pHeader = reinterpret_cast<const TPL_Header*>(m_textureData.pTextureData);
    return (pHeader && pHeader->magic == 0x20af30);
}

void Texture::LoadTexture()
{
    UnloadTexture();

    m_pTextureObject = new GXTexObj();

    if ( IsTplTexture())
    {
        LoadTplTexture();
    }
    else
    {
        LoadDefaultTexture();
    }
}

void Texture::UnloadTexture()
{

    if ( m_pGrrlibTexture )
	{
        GRRLIB_FreeTexture( m_pGrrlibTexture );
	}

    if ( m_pTextureObject )
    {
        delete m_pTextureObject;
    }

    if (  m_pTplTextureData )
    {
        free(m_pTplTextureData);
    }

    m_bTextureLoaded = false;
}

uint32_t Texture::GetWidth() const
{

    if ( m_bTextureLoaded )
	{
        return m_pGrrlibTexture->w;
	}
	return 0;
}

uint32_t Texture::GetHeight() const
{

    if ( m_bTextureLoaded )
	{
        return m_pGrrlibTexture->h;
	}
	return 0;
}

bool Texture::IsVisible() const
{
    return m_bVisible && m_bTextureLoaded;
}

void Texture::PrintTlpInfo()
{

#ifdef DEBUG
    if ( IsTplTexture())
    {
        // basic tlp info's
        const TPL_Header* header = reinterpret_cast<const TPL_Header*>(m_textureData.pTextureData);
        Debug::GetInstance().Log("magic %04x", header->magic );
        Debug::GetInstance().Log("texCount %d", header->texCount );
        Debug::GetInstance().Log("headerSize %d", header->headerSize );

        const TPL_Texture* texture = reinterpret_cast<const TPL_Texture*> ((m_textureData.pTextureData + sizeof(TPL_Header) + sizeof(TPL_Addr)));
        Debug::GetInstance().Log("Height %d", texture->height );
        Debug::GetInstance().Log("Width %d", texture->width );
        Debug::GetInstance().Log("Format %d", texture->format );
        Debug::GetInstance().Log("Maxlod %d", texture->maxLod );
        Debug::GetInstance().Log("EdgeLod %d", texture->edgeLod );
        Debug::GetInstance().Log("MinFilt %d", texture->minFilt );
        Debug::GetInstance().Log("MagFilt %d", texture->magFilt );
    }
#endif
}


ETextureType Texture::GetTextureType() const
{
	return SPRITE;
}

bool Texture::IsLoaded() const
{
    return m_bTextureLoaded;
}

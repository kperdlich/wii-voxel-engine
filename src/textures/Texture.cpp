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
    float       lodBias;
    uint8_t     edgeLod;
    uint8_t     minLod;
    uint8_t     maxLod;
    uint8_t     unpacked;
} TPL_Texture;

void Texture::LoadTPLTexture()
{
    m_textureObject = new GXTexObj();

    //const TPL_Header* pHeader = reinterpret_cast<const TPL_Header*>(m_textureData.pTextureData);
    //const TPL_Addr* pAddr =reinterpret_cast<const TPL_Addr*>((m_textureData.pTextureData + sizeof(TPL_Header)));
    const TPL_Texture* pTexture = reinterpret_cast<const TPL_Texture*>((m_textureLoadingData.textureData + sizeof(TPL_Header) + sizeof(TPL_Addr)));

    uint32_t size = m_textureLoadingData.textureSize - sizeof(TPL_Header) - sizeof(TPL_Addr) - sizeof(TPL_Texture);
    m_pTPLTextureData = memalign(32, size);
    memcpy(m_pTPLTextureData, (void*) (m_textureLoadingData.textureData + pTexture->dataOffs), size);

    DCFlushRange(m_pTPLTextureData, size);    

    GX_InitTexObj(m_textureObject, m_pTPLTextureData, pTexture->width, pTexture->height, pTexture->format, pTexture->wrap_s, pTexture->wrap_t, GX_FALSE);

    if (pTexture->maxLod)
    {
        GX_InitTexObjLOD(m_textureObject, pTexture->minFilt, pTexture->magFilt, pTexture->minLod, pTexture->maxLod, pTexture->lodBias, GX_DISABLE, pTexture->edgeLod, GX_ANISO_4);

        GX_InitTexObjEdgeLOD(m_textureObject, GX_ENABLE);
        GX_InitTexObjMaxAniso(m_textureObject, GX_ANISO_4);
    }
    else
    {
        GX_InitTexObjFilterMode(m_textureObject, pTexture->minFilt, pTexture->magFilt);
    }

    m_width = pTexture->width;
    m_height = pTexture->height;
    m_bTextureLoaded = true;
}


bool Texture::IsTPLTexture()
{
    const TPL_Header* pHeader = reinterpret_cast<const TPL_Header*>(m_textureLoadingData.textureData);
    return (pHeader && pHeader->magic == 0x20af30);
}

void Texture::Load()
{
    Unload();    

    if ( IsTPLTexture())
    {
        LoadTPLTexture();
    }
    else
    {
        BasicTexture::Load();      
    }
}

void Texture::Unload()
{
    if (  m_pTPLTextureData )
    {
        free(m_pTPLTextureData);
    }

    BasicTexture::Unload();   
}

Texture *Texture::Create(const uint8_t *textureData, uint32_t textureSize)
{
    TextureLoadingData txLoadingData = { textureData, textureSize };
    Texture* texture = new Texture( 0, 0, txLoadingData);
    texture->Load();
    return texture;
}

uint32_t Texture::GetWidth() const
{
   return m_width;
}

uint32_t Texture::GetHeight() const
{
   return m_height;
}

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


Texture::Texture(float x, float y, const unsigned char* texture, const u16 id ) : m_TextureBytes(texture), BasicTexture(x, y, id)
{
	m_Texture = NULL;
	m_visible = true;
}

Texture::~Texture()
{

}

GRRLIB_texImg* Texture::GetNativeTexture() const
{
	return this->m_Texture;
}

void Texture::LoadTexture() {

	if ( m_Texture )
	{
		GRRLIB_FreeTexture( m_Texture );
	}

	if ( m_TextureBytes )
	{
		m_Texture = GRRLIB_LoadTexture( m_TextureBytes );
	}
	else
	{
		m_Texture = GRRLIB_CreateEmptyTexture(rmode->fbWidth, rmode->efbHeight);
	}

	m_TextureLoaded = true;
}

void Texture::UnloadTexture()
{

	if ( m_Texture )
	{
		GRRLIB_FreeTexture( m_Texture );
	}
	m_TextureLoaded = false;
}

uint Texture::GetWidth() const
{

	if ( m_TextureLoaded )
	{
		return m_Texture->w;
	}
	return 0;
}

uint Texture::GetHeight() const
{

	if ( m_TextureLoaded )
	{
		return m_Texture->h;
	}
	return 0;
}

bool Texture::IsVisible() const
{
	return m_visible && m_TextureLoaded;
}

txTypes Texture::GetTextureType() const
{
	return SPRITE;
}

bool Texture::isLoaded() const
{
	return m_TextureLoaded;
}

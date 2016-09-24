/*
 * Texture.cpp
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */



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

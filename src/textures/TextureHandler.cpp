/*
 * TextureHandler.cpp
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */


#include "TextureHandler.h"
#include "../utils/Debug.h"
#include <functional>

TextureHandler::TextureHandler() {

}

TextureHandler::~TextureHandler() {
}


BasicTexture* TextureHandler::GetTextureByID(u16 index)
{
	for ( auto it = m_textures.begin(); it != m_textures.end(); it++)
	{
		if( (*it)->GetId() == index )
		{
			return (*it);
		}
	}

	return NULL;
}

void TextureHandler::DestroyTextureByName( const char* searchName )
{
	auto textureMapIt = m_textureMap.find( searchName );
	if ( textureMapIt != m_textureMap.end() )
	{
		(*textureMapIt->second)->UnloadTexture();
		delete (*textureMapIt->second);
		m_textures.erase( textureMapIt->second );
		m_textureMap.erase(searchName);
	}
}


void TextureHandler::DestroyAllTextures()
{
	if ( m_textures.empty() )
		 return;

	m_textureMap.clear();

	for ( auto it = m_textures.begin(); it != m_textures.end(); it++)
	{
		(*it)->UnloadTexture();
		delete (*it);
	}

	m_textures.clear();
}

Texture* TextureHandler::CreateTexture(const u8* textureName, const char* searchName )
{
	if ( FindTexture(searchName))
	{
		throw;
	}

	Texture* tex = new Texture( 0, 0, textureName, GetNewIndex() );
	tex->LoadTexture();
	std::vector<BasicTexture*>::iterator textureIt = m_textures.insert(m_textures.end(), tex );
	m_textureMap.insert( std::pair<std::string, std::vector<BasicTexture*>::iterator>(searchName, textureIt ));
	return tex;
}

u16 TextureHandler::GetNewIndex() const
{
	if ( !m_textures.empty() )
	{
		return m_textures.back()->GetId() + 1;
	}
	return 0;
}

const std::vector<BasicTexture*>* TextureHandler::GetTextures() const
{
	return &m_textures;
}

LabelTexture* TextureHandler::CreateLabel(int x, int y, const char* text,
		GRRLIB_ttfFont* font, uint fontSize, u32 color, const char* searchName)
{
	if ( FindTexture(searchName))
	{
		throw;
	}

	LabelTexture* label = new LabelTexture( text, x, y, GetNewIndex(), font, fontSize, color );
	label->LoadTexture();
	std::vector<BasicTexture*>::iterator labelIt = m_textures.insert(m_textures.end(), label );
	m_textureMap.insert(std::pair<std::string, std::vector<BasicTexture*>::iterator>(searchName, labelIt ));
	return label;
}

LabelTexture* TextureHandler::CreateLabel( const char* text, GRRLIB_ttfFont* font, const char* searchName )
{
	return CreateLabel(0, 0, text, font, DEFAULT_FONT_SIZE, GRRLIB_WHITE, searchName);
}


unsigned int TextureHandler::TextureCount() const
{
	return m_textures.size();
}

bool TextureHandler::FindTexture(std::string key) const
{
	auto textureMapIt = m_textureMap.find( key );
	return textureMapIt != m_textureMap.end();
}

const BasicTexture* TextureHandler::GetTexture(std::string key) const
{
	auto textureMapIt = m_textureMap.find( key );
	if ( textureMapIt != m_textureMap.end())
	{
		return (*textureMapIt->second);
	}

	return NULL;
}

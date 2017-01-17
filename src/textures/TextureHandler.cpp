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

    return nullptr;
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


Texture* TextureHandler::CreateTexture(const uint8_t* pTextureData, uint32_t textureSize, const char* pSearchName)
{
     // todo handle error!
    if ( FindTexture(pSearchName))
	{
		throw;
	}

    TextureData textureData = { pTextureData, textureSize };
    Texture* tex = new Texture( 0, 0, textureData, GetNewIndex() );
	tex->LoadTexture();
	std::vector<BasicTexture*>::iterator textureIt = m_textures.insert(m_textures.end(), tex );
    m_textureMap.insert( std::pair<std::string, std::vector<BasicTexture*>::iterator>(pSearchName, textureIt ));
	return tex;
}

Texture* TextureHandler::CreateTexture( const uint8_t* pTextureData, uint32_t textureSize, const char* pSearchName, bool visible )
{
    Texture* pTexture = CreateTexture(pTextureData, textureSize, pSearchName);
	pTexture->SetVisible(visible);
	return pTexture;
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
        GRRLIB_ttfFont* font, uint32_t fontSize, u32 color, const char* searchName)
{
    // todo handle error!
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


uint32_t TextureHandler::TextureCount() const
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

    return nullptr;
}

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


BasicTexture* TextureHandler::getTextureByID(u16 index)
{
	for ( std::vector<BasicTexture*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
	{
		if( (*it)->getId() == index )
		{
			return (*it);
		}
	}

	return NULL;
}

void TextureHandler::destroyTextureByName( const char* searchName )
{
	std::map<std::string, std::vector<BasicTexture*>::iterator>::iterator textureMapIt = m_textureMap.find( searchName );
	if ( textureMapIt != m_textureMap.end() )
	{
		(*textureMapIt->second)->unloadTexture();
		delete (*textureMapIt->second);
		m_textures.erase( textureMapIt->second );
		m_textureMap.erase(searchName);
	}
}


void TextureHandler::destroyAllTextures()
{
	if ( m_textures.empty() )
		 return;

	m_textureMap.clear();

	for ( std::vector<BasicTexture*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
	{
		(*it)->unloadTexture();
		delete (*it);
	}

	m_textures.clear();
}

Texture* TextureHandler::createTexture(const u8* textureName, const char* searchName )
{
	if ( FindTexture(searchName))
	{
		throw;
	}

	Texture* tex = new Texture( 0, 0, textureName, getNewIndex() );
	tex->loadTexture();
	std::vector<BasicTexture*>::iterator textureIt = m_textures.insert(m_textures.end(), tex );
	m_textureMap.insert( std::pair<std::string, std::vector<BasicTexture*>::iterator>(searchName, textureIt ));
	return tex;
}

u16 TextureHandler::getNewIndex()
{
	if ( !m_textures.empty() )
	{
		return m_textures.back()->getId() + 1;
	}
	return 0;
}

/*Tile* TextureHandler::createTile(int x, int y, int index, SpriteSheet* spriteSheet) {
	Tile* tile = new Tile( x, y, index, spriteSheet, getNewIndex() );
	m_Textures.push_back( tile );
	return tile;
}*/

std::vector<BasicTexture*>* TextureHandler::getTextures() {
	return &m_textures;
}

/*SpriteSheet* TextureHandler::createTilemap(const u8* textureName) {
	SpriteSheet* spriteSheet = new SpriteSheet( textureName, getNewIndex() );
	spriteSheet->loadTexture();
	m_Textures.push_back( spriteSheet );
	return spriteSheet;
}*/

LabelTexture* TextureHandler::createLabel(int x, int y, const char* text,
		GRRLIB_ttfFont* font, uint fontSize, u32 color, const char* searchName)
{
	if ( FindTexture(searchName))
	{
		throw;
	}

	LabelTexture* label = new LabelTexture( text, x, y, getNewIndex(), font, fontSize, color );
	label->loadTexture();
	std::vector<BasicTexture*>::iterator labelIt = m_textures.insert(m_textures.end(), label );
	m_textureMap.insert(std::pair<std::string, std::vector<BasicTexture*>::iterator>(searchName, labelIt ));
	return label;
}

LabelTexture* TextureHandler::createLabel( const char* text, GRRLIB_ttfFont* font, const char* searchName )
{
	return createLabel(0, 0, text, font, DEFAULT_FONT_SIZE, GRRLIB_WHITE, searchName);
}


unsigned int TextureHandler::TextureCount()
{
	return m_textures.size();
}

bool TextureHandler::FindTexture(std::string key)
{
	std::map<std::string, std::vector<BasicTexture*>::iterator>::iterator textureMapIt = m_textureMap.find( key );
	return textureMapIt != m_textureMap.end();
}

BasicTexture* TextureHandler::GetTexture(std::string key)
{
	std::map<std::string, std::vector<BasicTexture*>::iterator>::iterator textureMapIt = m_textureMap.find( key );
	if ( textureMapIt != m_textureMap.end())
	{
		return (*textureMapIt->second);
	}

	return NULL;
}

/*
 * TextureHandler.cpp
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */


#include "TextureHandler.h"
#include "../utils/Debug.h"

TextureHandler::TextureHandler() {

}

TextureHandler::~TextureHandler() {
}


BasicTexture* TextureHandler::getTextureByID(u16 index)
{
	for ( std::vector<BasicTexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); )
	{
		if( (*it)->getId() == index )
		{
			return (*it);
		}
	}

	return NULL;
}

void TextureHandler::destroyTextureByID( u16 index )
{
	for ( std::vector<BasicTexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); )
	{
	   if( (*it)->getId() == index )
	   {
		  (*it)->unloadTexture();
		  delete *it;
		  m_Textures.erase(it);
		  return;
	   }
	   else
	   {
		  ++it;
	   }
	}
}

void TextureHandler::destroyAllTextures()
{
	if ( m_Textures.empty() )
		 return;

	for ( std::vector<BasicTexture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		(*it)->unloadTexture();
		 delete *it;
	}

	m_Textures.clear();
}

Texture* TextureHandler::createTexture(const u8* textureName ) {

	Texture* tex = new Texture( 0, 0, textureName, getNewIndex() );
	tex->loadTexture();
	m_Textures.push_back( tex );
	return tex;
}

u16 TextureHandler::getNewIndex()
{
	if ( !m_Textures.empty() )
	{
		return m_Textures.back()->getId() + 1;
	}
	return 0;
}

Tile* TextureHandler::createTile(int x, int y, int index, SpriteSheet* spriteSheet) {
	Tile* tile = new Tile( x, y, index, spriteSheet, getNewIndex() );
	m_Textures.push_back( tile );
	return tile;
}

std::vector<BasicTexture*>* TextureHandler::getTextures() {
	return &m_Textures;
}

SpriteSheet* TextureHandler::createTilemap(const u8* textureName) {
	SpriteSheet* spriteSheet = new SpriteSheet( textureName, getNewIndex() );
	spriteSheet->loadTexture();
	m_Textures.push_back( spriteSheet );
	return spriteSheet;
}

LabelTexture* TextureHandler::createLabel(int x, int y, const char* text,
		GRRLIB_ttfFont* font, uint fontSize, u32 color) {

	LabelTexture* label = new LabelTexture( text, x, y, getNewIndex(), font, fontSize, color );
	label->loadTexture();
	m_Textures.push_back( label );
	return label;
}

LabelTexture* TextureHandler::createLabel( const char* text, GRRLIB_ttfFont* font )
{
	return createLabel(0, 0, text, font, DEFAULT_FONT_SIZE, GRRLIB_WHITE);
}

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
	for( uint i = 0; i < m_Textures.size(); i++ )
	{
		if ( static_cast<BasicTexture*>(m_Textures[ i ])->getId() == index )
		{
			return m_Textures[ i ];
		}
	}
	return NULL;
}

void TextureHandler::destroyTextureByID( u16 index )
{
	for( uint i = 0; i < m_Textures.size(); i++ )
	{
		if ( static_cast<BasicTexture*>(m_Textures[ i ])->getId() == index )
		{
			m_Textures[ i ]->unloadTexture();
			m_Textures.erase( m_Textures.begin() + i );
			delete m_Textures[ i ];
			return;
		}
	}
}

void TextureHandler::destroyAllTextures() {

	for (u16 i = 0; i < m_Textures.size(); i++)
	{
		destroyTextureByID( static_cast<BasicTexture*>(m_Textures[i])->getId() );
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
	if ( m_Textures.size() > 0 )
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

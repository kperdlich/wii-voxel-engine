/*
 * FontHandler.cpp
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */


#include "FontHandler.h"

FontHandler::FontHandler() {
}

FontHandler::~FontHandler() {

	for ( uint i = 0; i < m_fonts.size(); i++ )
	{
		GRRLIB_FreeTTF (m_fonts[ i ]);
	}

	m_fonts.clear();
}

void FontHandler::init() {
	createFont( FreeMonoBold_ttf, FreeMonoBold_ttf_size );
	createFont( Minecraft_ttf, Minecraft_ttf_size );
}

void FontHandler::createFont( const u8* file_base, s32 file_size ) {
	GRRLIB_ttfFont* ttfFont = GRRLIB_LoadTTF( file_base, file_size );
	m_fonts.push_back( ttfFont );
}

GRRLIB_ttfFont* FontHandler::getNativFontByID( uint id ) {
	if ( id >= 0 && id < m_fonts.size() )
	{
		return m_fonts[ id ];
	}

	return NULL;
}

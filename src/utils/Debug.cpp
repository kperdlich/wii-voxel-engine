/*
 * Debug.cpp
 *
 *  Created on: 26.06.2015
 *      Author: Kevin
 */

#include "Debug.h"

static void debug( const char *str, int x, int y )
{
	GRRLIB_PrintfTTF( x, y, Controller::getInstance().getFontHandler()->getNativFontByID( DEFAULT_FONT_ID ), str, DEFAULT_FONT_SIZE, GRRLIB_RED );
}

Debug::Debug() {


}

Debug::~Debug() {

}

void Debug::log(char* msg) {
	m_logs.push_back( msg );
}

void Debug::print() {
	int y = DEBUG_LINE;
	for (int i = 0; i < m_logs.size(); i++)
	{
		debug(m_logs[i], 0, y);

		if ( y >= 450 )
		{
			y = DEBUG_LINE;
		}
		else
		{
			y += 10;
		}
	}
}

void Debug::clear() {
	for (int i = 0; i < m_logs.size(); i++)
	{
		delete [] m_logs[i];
	}
	m_logs.clear();
}




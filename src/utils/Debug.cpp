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

#include "Debug.h"

static void debug( const char *str, int x, int y )
{
	GRRLIB_PrintfTTF( x, y, Controller::GetInstance().GetFontHandler().GetNativFontByID( DEFAULT_FONT_ID ), str, DEFAULT_FONT_SIZE, GRRLIB_WHITE );
}

Debug::Debug() {


}

Debug::~Debug() {

}

void Debug::Log(char* msg)
{
	m_logs.push_back( msg );
}

void Debug::Print()
{
	int y = DEBUG_LINE;
	for (unsigned int i = 0; i < m_logs.size(); i++)
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

void Debug::Clear() {
	/*for (unsigned int i = 0; i < m_logs.size(); i++)
	{
		delete [] m_logs[i];
	}*/
	m_logs.clear();
}




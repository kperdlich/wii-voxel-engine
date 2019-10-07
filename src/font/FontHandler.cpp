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


#include "font/FontHandler.h"
#include "utils/Debug.h"

FontHandler::~FontHandler() {

    for (uint32_t i = 0; i < m_fonts.size(); i++)
	{
        GRRLIB_FreeTTF (m_fonts[i]);
	}

	m_fonts.clear();
}

void FontHandler::Init()
{
    CreateFont(FreeMonoBold_ttf, FreeMonoBold_ttf_size);
    CreateFont(Minecraft_ttf, Minecraft_ttf_size);
}

void FontHandler::CreateFont( const u8* file_base, s32 file_size ) {
	GRRLIB_ttfFont* ttfFont = GRRLIB_LoadTTF( file_base, file_size );
    m_fonts.push_back(ttfFont);
}

GRRLIB_ttfFont* FontHandler::GetNativFontByID( uint32_t id ) {
    if (id >= 0 && id < m_fonts.size())
	{
        return m_fonts[id];
	}

    return nullptr;
}

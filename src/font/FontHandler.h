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

#ifndef _FONTHANDLER_H_
#define _FONTHANDLER_H_

#include "../core/grrlib.h"
#include <vector>
// Font
#include "FreeMonoBold_ttf.h"
#include "Minecraft_ttf.h"


#define DEFAULT_FONT_SIZE 12


class FontHandler {

private:
	std::vector<GRRLIB_ttfFont*> m_fonts;

public:
	FontHandler();
	~FontHandler();
	void Init();
	void CreateFont(const u8* file_base, s32 file_size);
	GRRLIB_ttfFont* GetNativFontByID( uint id );

};


#endif /* _FONTHANDLER_H_ */

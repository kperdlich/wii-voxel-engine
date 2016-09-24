/*
 * FontHandler.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

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

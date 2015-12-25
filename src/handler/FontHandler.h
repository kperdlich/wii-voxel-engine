/*
 * FontHandler.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef SRC_GUI_FONTHANDLER_H_
#define SRC_GUI_FONTHANDLER_H_

#include <grrlib.h>
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
	void init();
	void createFont(const u8* file_base, s32 file_size);
	GRRLIB_ttfFont* getNativFontByID( uint id );

};


#endif /* SRC_GUI_FONTHANDLER_H_ */

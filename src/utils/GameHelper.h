/*
 * GameHelper.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef _GAMEHELPER_H_
#define _GAMEHELPER_H_

#include <stdarg.h>
#include <ogc/lwp_watchdog.h>

#include "../Controller.h"
#include "../core/grrlib.h"
#include "../font/FontHandler.h"
#include "../utils/ColorHelper.h"

u8 calculateFrameRate();
void printFps(unsigned int x, unsigned int y, GRRLIB_ttfFont* font, unsigned int fontSize, const u32 color );
void printGameVersion(unsigned int x, unsigned int y, GRRLIB_ttfFont* font, unsigned int fontSize, const u32 color);
char* getResolution();

#endif /* _GAMEHELPER_H_ */

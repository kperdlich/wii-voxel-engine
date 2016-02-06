/*
 * GameHelper.h
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */

#ifndef SRC_UTILS_GAMEHELPER_H_
#define SRC_UTILS_GAMEHELPER_H_

#include <stdarg.h>
#include <ogc/lwp_watchdog.h>

#include "../core/grrlib.h"
#include "../handler/Controller.h"
#include "../handler/FontHandler.h"
#include "../gui/ColorHelper.h"

u8 calculateFrameRate();
void printFps(unsigned int x, unsigned int y, GRRLIB_ttfFont* font, unsigned int fontSize, const u32 color );
void printGameVersion(unsigned int x, unsigned int y, GRRLIB_ttfFont* font, unsigned int fontSize, const u32 color);
char* getResolution();

#endif /* SRC_UTILS_GAMEHELPER_H_ */

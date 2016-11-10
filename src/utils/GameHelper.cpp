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


#include "GameHelper.h"

static char* GameName =  "WoxelCraft";
static char* BuildVersion = "0.0.3";

static u8 frameCount = 0;
static u32 fpsLastTime;
static u8 fps = 0;

u8 calculateFrameRate()
{
    u32 currentTime = ticks_to_millisecs(gettime());

    frameCount++;
    if(currentTime - fpsLastTime > 1000) {
    	fpsLastTime = currentTime;
    	fps = frameCount;
        frameCount = 0;
    }
    return fps;
}

void printFps(unsigned int x, unsigned int y, GRRLIB_ttfFont* font, unsigned int fontSize, const u32 color )
{
	char buffer[20];
	sprintf(buffer, "FPS: %d", fps);
	GRRLIB_PrintfTTF( x, y, font, buffer, fontSize, color );
}

void printGameVersion(unsigned int x, unsigned int y, GRRLIB_ttfFont* font, unsigned int fontSize, const u32 color)
{
	char buffer[sizeof(GameName) + sizeof(BuildVersion) + 2];
	sprintf(buffer, "%s %s", GameName, BuildVersion);
	GRRLIB_PrintfTTF( x, y, font, buffer, fontSize, color );
}

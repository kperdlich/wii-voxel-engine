/*
 * GameHelper.cpp
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */


#include "GameHelper.h"

static char* GameName =  "GameCraft";
static char* BuildVersion = "0.0.1";

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

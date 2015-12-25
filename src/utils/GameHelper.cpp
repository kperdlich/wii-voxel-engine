/*
 * GameHelper.cpp
 *
 *  Created on: 17.05.2015
 *      Author: Kevin
 */


#include "GameHelper.h"

static char* GameName =  "WiiCraft";
static char* BuildVersion = "1.0.0";

static u8 frameCount = 0;
static u32 lastTime;
static u8 FPS = 0;

u8 calculateFrameRate() {
    u32 currentTime = ticks_to_millisecs(gettime());

    frameCount++;
    if(currentTime - lastTime > 1000) {
        lastTime = currentTime;
        FPS = frameCount;
        frameCount = 0;
    }
    return FPS;
}

void printFps(unsigned int x, unsigned int y, GRRLIB_ttfFont* font, unsigned int fontSize, const u32 color )
{
	char buffer[20];
	sprintf(buffer, "FPS: %d", FPS);
	GRRLIB_PrintfTTF( x, y, font, buffer, fontSize, color );
}

void printGameVersion(unsigned int x, unsigned int y, GRRLIB_ttfFont* font, unsigned int fontSize, const u32 color)
{
	char buffer[sizeof(GameName) + sizeof(BuildVersion) + 2];
	sprintf(buffer, "%s %s", GameName, BuildVersion);
	GRRLIB_PrintfTTF( x, y, font, buffer, fontSize, color );
}

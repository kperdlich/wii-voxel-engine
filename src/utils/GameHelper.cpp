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


#include "Engine.h"
#include "renderer/displaylist.h"
#include "utils/GameHelper.h"

static uint8_t fps = 0;

uint8_t CalculateFrameRate()
{
	static uint8_t frameCount = 0;
	static uint32_t fpsLastTime;

	uint32_t currentTime = ticks_to_millisecs(gettime());

	frameCount++;
	if (currentTime - fpsLastTime > 1000)
	{
		fpsLastTime = currentTime;
		fps = frameCount;
		frameCount = 0;
	}

	return fps;
}

void PrintFPS(uint32_t x, uint32_t y, GRRLIB_ttfFont* font, uint32_t fontSize, const u32 color)
{
    char fpsBuffer[10];
    sprintf(fpsBuffer, "FPS: %d", fps);
    GRRLIB_PrintfTTF(x, y, font, fpsBuffer, fontSize, color);
}

void PrintDebugPanel(uint32_t x, uint32_t y, GRRLIB_ttfFont* font, uint32_t fontSize, const u32 color)
{
	char buffer[20];
    char memoryBuffer[20];
    char displayListBuffer[20];
	sprintf(buffer, "%s %s", GAME_NAME, BUILD_VERSION);
    sprintf(memoryBuffer, "Heap: %.2f MB", (float) GetCurrentHeapMemory() / 1048576.0f);
    sprintf(displayListBuffer, "DPL Heap: %.2f MB", (float) GetGlobalDisplayListSize() / 1048576.0f);
	GRRLIB_PrintfTTF(x, y, font, buffer, fontSize, color);
    GRRLIB_PrintfTTF(x, y + 20, font, memoryBuffer, fontSize, color);
    GRRLIB_PrintfTTF(x, y + 40, font, displayListBuffer, fontSize, color);
}

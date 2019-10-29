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

#pragma once

#include <stdarg.h>
#include <ogc/lwp_watchdog.h>

#include "Engine.h"
#include "core/grrlib.h"
#include "font/FontHandler.h"
#include "utils/ColorHelper.h"

uint8_t CalculateFrameRate();
void PrintFPS(uint32_t x, uint32_t y, GRRLIB_ttfFont* font, uint32_t fontSize, const u32 color);
void PrintDebugPanel(uint32_t x, uint32_t y, GRRLIB_ttfFont* font, uint32_t fontSize, const u32 color);

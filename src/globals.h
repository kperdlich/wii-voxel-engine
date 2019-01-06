/***
 *
 * Copyright (C) 2018 DaeFennek
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

#ifndef GLOBALS_H
#define GLOBALS_H

#define DEBUG
#define DOLPHIN

#define GAME_NAME                   "WoxelCraft"
#define BUILD_VERSION               "0.0.8"

#define SERVER_PROTOCOL_VERSION     29

#define DEFAULT_FONT_ID             0
#define DEFAULT_MINECRAFT_FONT_ID   1

#define FILE_PATH   "apps/WoxelCraft"
#define WORLD_PATH  FILE_PATH "/world"

#define LOG_FILE    FILE_PATH "/Log.txt"
#define SEED_FILE   WORLD_PATH "/Seed.dat"


#ifdef DOLPHIN
    #define SERVER_IP "127.0.0.1"
#else
    #define SERVER_IP "192.168.0.143"
#endif

#endif // GLOBALS_H

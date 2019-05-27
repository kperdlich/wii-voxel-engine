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

#pragma once

#define PACKET_KEEP_ALIVE               0x00
#define PACKET_LOGIN                    0x01
#define PACKET_HANDSHAKE                0x02
#define PACKET_CHAT_MESSAGE             0x03
#define PACKET_TIME_UPDATE              0x04
#define PACKET_ENTITY_EQUIPMENT         0x05
#define PACKET_SPAWN_POSITION           0x06
#define PACKET_USE_ENTITY               0x07
#define PACKET_UPDATE_HEALTH            0x08
#define PACKET_RESPAWN                  0x09
#define PACKET_PLAYER                   0x0A
#define PACKET_PLAYER_POSITION          0x0B
#define PACKET_PLAYER_LOOK              0x0C
#define PACKET_PLAYER_POSITION_AND_LOOK 0x0D
#define PACKET_PLAYER_DIGGING           0x0E
#define PACKET_PLAYER_BLOCK_PLACEMENT   0x0F
#define PACKET_HELD_ITEM_CHANGE         0x10
#define PACKET_USE_BED                  0x11
#define PACKET_ANIMATION                0x12
#define PACKET_ENTITY_ACTION            0x13
#define PACKET_SPAWN_NAMED_ENTITY       0x14
#define PACKET_SPAWN_DROPPED_ITEM       0x15
#define PACKET_COLLECT_ITEM             0x16
#define PACKET_SPAWN_OBJECT             0x17
#define PACKET_SPAWN_MOB                0x18
#define PACKET_SPAWN_PAINTING           0x19
#define PACKET_SPAWN_EXPERIENCE_ORB     0x1A
#define PACKET_ENTITY_VELOCITY          0x1C
#define PACKET_DESTROY_ENTITY           0x1D
#define PACKET_ENTITY                   0x1E
#define PACKET_ENTITY_RELATIVE_MOVE     0x1F
#define PACKET_ENTITY_LOOK              0x20
#define PACKET_ENTITY_LOOK_RELATIVE_MOVE 0x21
#define PACKET_ENTITY_TELEPORT          0x22
#define PACKET_ENTITY_HEAD_LOOK         0x23
#define PACKET_ENTITY_STATUS            0x26
#define PACKET_ATTACH_ENTITY            0x27
#define PACKET_ENTITY_METADATA          0x28
#define PACKET_ENTITY_EFFECT            0x29
#define PACKET_REMOVE_ENTITY_EFFECT     0x2A
#define PACKET_SET_EXPERIENCE           0x2B
#define PACKET_CHUNK_ALLOCATION         0x32
#define PACKET_CHUNK_DATA               0x33
#define PACKET_MULTI_BLOCK_CHANGE       0x34
#define PACKET_BLOCK_CHANGE             0x35
#define PACKET_BLOCK_ACTION             0x36
#define PACKET_EXPLOSION                0x3C
#define PACKET_SOUND_EFFECT             0x3D
#define PACKET_CHANGE_GAME_STATE        0x46
#define PACKET_THUNDERBOLT              0x47
#define PACKET_OPEN_WINDOW              0x64
#define PACKET_CLOSE_WINDOW             0x65
#define PACKET_CLICK_WINDOW             0x66
#define PACKET_SET_SLOT                 0x67
#define PACKET_SET_WINDOW_ITEMS         0x68
#define PACKET_UPDATE_WINDOW_PROPERTY   0x69
#define PACKET_CONFIRM_TRANSACTION      0x6A
#define PACKET_CREATIVE_INVENTORY_ACTION 0x6B
#define PACKET_ENCHANT_ITEM             0x6C
#define PACKET_UPDATE_SIGN              0x82
#define PACKET_ITEM_DATA                0x83
#define PACKET_UPDATE_TILE_ENTITY       0x84
#define PACKET_INCREMENT_STATISTICS     0xC8
#define PACKET_PLAYER_LIST_ITEM         0xC9
#define PACKET_PLAYER_ABILITIES         0xCA
#define PACKET_PLUGIN_MESSAGE           0xFA
#define PACKET_SERVER_LIST_PING         0xFE
#define PACKET_DISCONNECT               0xFF


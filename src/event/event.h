#pragma once

#include <stdint.h>

constexpr uint32_t EVENT_SERVER_CONNECTED = 0;
constexpr uint32_t EVENT_SERIALIZED_ALL_CHUNKS = 1;
constexpr uint32_t EVENT_PREPARE_WORLD = 2;
constexpr uint32_t EVENT_RECEIVED_CHUNKS_FROM_SERVER = 3;
constexpr uint32_t EVENT_SERVER_CONNECTION_FAILED = 4;
constexpr uint32_t EVENT_SEND_PLAYER_INFO_TO_SERVER = 5;

struct Event
{
	uint32_t ID;
	void* Payload;
};

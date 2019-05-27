#pragma once

#include <stdint.h>

#define EVENT_SERVER_CONNECTED              0
#define EVENT_SERIALIZED_ALL_CHUNKS         1
#define EVENT_PREPARE_WORLD                 2
#define EVENT_RECEIVED_CHUNKS_FROM_SERVER   3
#define EVENT_SERVER_CONNECTION_FAILED      4
#define EVENT_SEND_PLAYER_INFO_TO_SERVER    5

struct Event
{
    uint32_t ID;
    void* Payload;
};

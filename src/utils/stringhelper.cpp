#include "stringhelper.h"

uint32_t WriteNetworkString(char* buffer, const char* const str, uint32_t len, uint32_t pos)
{
    for(uint32_t i = 0; i < len; ++i)
    {
        buffer[pos++] = 0;
        buffer[pos++] = str[i];
    }

    return len * 2;
}

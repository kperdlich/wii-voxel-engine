#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <string>
#include <sstream>

uint32_t WriteNetworkString(char* buffer, const char* const str, uint32_t len, uint32_t pos = 0);

template<typename T>
std::string ToString(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}





#endif // STRINGHELPER_H

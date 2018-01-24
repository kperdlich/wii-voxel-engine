#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <string>
#include <sstream>

template<typename T>
std::string ToString(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

#endif // STRINGHELPER_H

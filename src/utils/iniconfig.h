#pragma once

#include <string>
#include "inipp.h"

class IniConfig
{
public:
    void Parse(const std::string& file);

    template<typename T>
    T GetValue(const std::string& section, const std::string& name)
    {
        T value;
        inipp::extract(m_iniFile.sections[section][name], value);
        return value;
    }

private:
     inipp::Ini<char> m_iniFile;
};

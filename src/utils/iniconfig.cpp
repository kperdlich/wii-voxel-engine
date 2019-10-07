#include <fstream>
#include <stdexcept>
#include "iniconfig.h"
#include "Debug.h"

IniConfig::IniConfig() {}

void IniConfig::Parse(const std::string& file)
{
    std::ifstream iniFile(file);
    m_iniFile.parse(iniFile);
    if (m_iniFile.errors.size() > 0)
    {
        for (const auto& err : m_iniFile.errors)
        {
            ERROR("Error while parsing %s: %s", file.c_str(), err.c_str());
        }
        throw std::runtime_error("Error while parsing .ini!");
    }
    m_iniFile.default_section(m_iniFile.sections["Default"]);
    m_iniFile.interpolate();
}

#include <ogc/lwp_watchdog.h>
#include "utils/clock.h"

Clock::Clock() {}

void Clock::Start()
{
    m_milliSecs = ticks_to_millisecs(gettime());
}

void Clock::Stop()
{
    m_milliSecs = ticks_to_millisecs(gettime()) - m_milliSecs;
}

uint64_t Clock::GetMilliSecs() const
{
    return m_milliSecs;
}

float Clock::GetSecs() const
{
   return m_milliSecs / 1000.0f;
}

#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

class Clock
{
public:
    Clock();
    void Start();
    void Stop();
    uint64_t GetMilliSecs() const;
    float GetSecs() const;

private:
    uint64_t m_milliSecs;
};

#endif // CLOCK_H

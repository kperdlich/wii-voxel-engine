#pragma once

#include <stdint.h>

class Clock
{
public:
	Clock();
	Clock(const Clock&) = delete;
	Clock(Clock&&) = delete;
	void operator=(const Clock&) = delete;
	void operator=(Clock&&) = delete;
	void Start();
	void Stop();
	uint64_t GetMilliSecs() const;
	float GetSecs() const;

private:
	uint64_t m_milliSecs;
};

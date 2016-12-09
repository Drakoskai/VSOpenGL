#pragma once

#include <windows.h>
#include <cstdint>
#include <cassert>

class SimpleTimer
{
public:
	SimpleTimer()
		: m_frequency(0), m_startTime(0), m_deltaTime(0), m_beginTime(0), m_endTime(0)
	{
		int64_t frequency;
		QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
		assert(frequency != 0);
		m_frequency = static_cast<float>(frequency);
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_startTime));
	}

	~SimpleTimer() { }

	void Start()
	{
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_beginTime));
	}

	void Update()
	{
		int64_t currentTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentTime));
		int64_t elapsedTicks = currentTime - m_startTime;
		m_deltaTime = static_cast<float>(elapsedTicks) / m_frequency;
		m_startTime = currentTime;
	}

	void End()
	{
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_endTime));
	}

	float GetDeltaTime() const
	{
		return m_deltaTime;
	}

private:
	float m_frequency;
	int64_t m_startTime;
	float m_deltaTime;
	int64_t m_beginTime;
	int64_t m_endTime;
};

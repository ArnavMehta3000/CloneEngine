#include "Utilities/Timer.h"

namespace Clone::Utls
{
	Timer::Timer()
		:
		m_deltaTime(0.0)
	{
		m_lastTime = std::chrono::high_resolution_clock::now();
	}

	void Timer::Tick()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - m_lastTime);
		m_deltaTime = duration.count() / 1e6; // Convert microseconds to seconds
		m_lastTime = currentTime;
	}

	double Timer::GetDeltaTime()
	{
		return m_deltaTime;
	}
}
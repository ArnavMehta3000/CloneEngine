#pragma once
#include <chrono>

namespace Clone::Utls
{
	class Timer
	{
	public:
		Timer();
		void Tick();

		double GetDeltaTime();

	private:
		std::chrono::high_resolution_clock::time_point m_lastTime;
		double m_deltaTime;
	};
}
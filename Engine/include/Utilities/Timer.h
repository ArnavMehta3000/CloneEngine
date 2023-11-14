#pragma once
#include <chrono>

namespace Clone::Utls
{
	/// <summary>
	/// Simple time class that starts on construction
	/// </summary>
	class Timer
	{
	public:
		Timer();

		/// <summary>
		/// Function to advance (tick) the timer
		/// </summary>
		void Tick();

		/// <summary>
		/// Returns the value between the last tick call
		/// </summary>
		/// <returns>Time since last tick in seconds</returns>
		double GetDeltaTime();

	private:
		std::chrono::high_resolution_clock::time_point m_lastTime;
		double m_deltaTime;
	};
}
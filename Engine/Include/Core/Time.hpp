#pragma once 

#include <chrono>
#include <Util/Types.hpp>

namespace blox
{
	class Time
	{
	private:
		static Time time;

		float deltaTime = 0.0f;
		std::chrono::steady_clock::time_point previousTime = std::chrono::high_resolution_clock::now();

	public:
		static void Update();

		static ulong GetTime();
		static float GetDeltaTime();
	};
}


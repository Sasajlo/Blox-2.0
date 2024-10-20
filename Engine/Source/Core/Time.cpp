#include <Core/Time.hpp>

using namespace blox;

Time Time::time;

void Time::Update()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = currentTime - Time::time.previousTime;
	Time::time.deltaTime = duration.count();
	Time::time.previousTime = currentTime;
}

ulong Time::GetTime()
{
	auto now = std::chrono::steady_clock::now();

	// Convert the time point to milliseconds
	return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

float Time::GetDeltaTime()
{
	return Time::time.deltaTime;
}

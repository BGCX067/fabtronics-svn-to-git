#include "Clock.h"

Clock::Clock(void)
{
}

Clock::~Clock(void)
{
}

bool Clock::Initialize()
{
	auto b = QueryPerformanceFrequency(&timeFrequency);
	if ( !b )
		return false;
	b = QueryPerformanceCounter(&timeLastFrame);
	if ( !b )
		return false;
	return true;
}

bool Clock::Shutdown()
{
	return true;
}
void Clock::NewFrame()
{
	LARGE_INTEGER thisTime;
	QueryPerformanceCounter(&thisTime);

	LARGE_INTEGER delta;
	delta.QuadPart = thisTime.QuadPart - timeLastFrame.QuadPart;
	deltaTime = ((float)delta.QuadPart) / timeFrequency.QuadPart;

	timeLastFrame = thisTime;
}

float Clock::TimeElapsedLastFrame()
{
	return deltaTime;
}

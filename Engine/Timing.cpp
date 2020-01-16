#include "Timing.h"
#include <profileapi.h>

void Timing::startTime()
{

	return 0.0f;
}

float Timing::deltaTime()
{
	static long g_LastFrameTick = 0;
	float g_LastFrameTime_ms;

	long currentTick = GetCurrentCPUCounter();
	return 0.0f;
}

long Timing::GetCurrentCPUCounter()
{
	LARGE_INTEGER* currTick = new LARGE_INTEGER;
	QueryPerformanceCounter(currTick);
	return currTick;
}

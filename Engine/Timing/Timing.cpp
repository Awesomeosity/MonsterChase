#include "Timing.h"
#include <windows.h>

void Timing::startTime()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastTick);
	return;
}

float Timing::deltaTime()
{
	LARGE_INTEGER currentTick, diffTick;
	QueryPerformanceCounter(&currentTick);

	diffTick.QuadPart = lastTick.QuadPart - currentTick.QuadPart;
	diffTick.QuadPart *= 1000000000;
	diffTick.QuadPart /= frequency.QuadPart;

	lastTick = currentTick;

	return diffTick.QuadPart;
}
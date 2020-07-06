#include "Timing.h"
#include <windows.h>
static LARGE_INTEGER frequency;
static LARGE_INTEGER lastTick;

void Timing::startTime()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&lastTick);
	return;
}

//Returns diff in milliseconds
long Timing::deltaTime()
{
	LARGE_INTEGER currentTick, diffTick;
	QueryPerformanceCounter(&currentTick);

	diffTick.QuadPart = currentTick.QuadPart - lastTick.QuadPart;
	diffTick.QuadPart *= 1000000;
	diffTick.QuadPart /= frequency.QuadPart;

	lastTick = currentTick;

	return (long)diffTick.QuadPart;
}
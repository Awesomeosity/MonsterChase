#pragma once
#include <windows.h>

class Timing
{
public:
	static void startTime();
	static float deltaTime();
private:
	Timing();
	static LARGE_INTEGER frequency;
	static LARGE_INTEGER lastTick;
};


#pragma once
#include <windows.h>

class Timing
{
public:
	static void startTime();
	static long deltaTime();
private:
	Timing();
};


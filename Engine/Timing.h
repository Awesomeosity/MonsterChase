#pragma once
class Timing
{
public:
	void startTime();
	float deltaTime();
private:
	long GetCurrentCPUCounter();

	LARGE_INTEGER frequency;
};


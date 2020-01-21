#pragma once
#include <windows.h>
class PhysicsData;
class Point2D;
class Physics
{
public:
	static void calcNewPos(float dt_ms, PhysicsData* data, Point2D forces);
private:
	Physics();
};


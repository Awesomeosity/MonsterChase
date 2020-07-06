#pragma once
#include "../Types/Point2D.h"
class GameObject;
class PhysicsData
{
public:
	PhysicsData();
	PhysicsData(float _mass, float _drag);

	Point2D GetPrevPos();
	float GetMass();
	float GetDrag();
private:
	float mass;
	float drag;
	Point2D prevPos;
};


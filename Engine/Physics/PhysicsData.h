#pragma once
#include "../Types/Point2D.h"
class GameObject;
class PhysicsData
{
public:
	PhysicsData();
	PhysicsData(GameObject* _object, float _mass, float _drag);

	Point2D GetPrevPos();
	void UpdatePrevPos(Point2D point);
	Point2D GetCurrentPos();
	float GetMass();
	float GetDrag();
private:
	GameObject* object;
	float mass;
	float drag;
	Point2D prevPos;
};


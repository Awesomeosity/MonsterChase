#include "PhysicsData.h"
#include "../Objects/GameObject.h"
PhysicsData::PhysicsData() :
	object(nullptr), mass(0), drag(0), prevPos()
{
}

PhysicsData::PhysicsData(GameObject* _object, float _mass, float _drag) :
	object(_object), mass(_mass), drag(_drag), prevPos()
{
}

Point2D PhysicsData::GetPrevPos()
{
	return prevPos;
}
//Updates the previous position of this object
void PhysicsData::UpdatePrevPos(Point2D point)
{
	prevPos = *((*object).GetPoint());
	(*object).SetPoint(point);
}

Point2D PhysicsData::GetCurrentPos()
{
	return *(*object).GetPoint();
}

float PhysicsData::GetMass()
{
	return mass;
}

float PhysicsData::GetDrag()
{
	return drag;
}
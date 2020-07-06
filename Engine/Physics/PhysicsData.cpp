#include "PhysicsData.h"
#include "../Objects/GameObject.h"
PhysicsData::PhysicsData() :
	mass(0), drag(0), prevPos()
{
}

PhysicsData::PhysicsData(float _mass, float _drag) :
	mass(_mass), drag(_drag), prevPos()
{
}

Point2D PhysicsData::GetPrevPos()
{
	return prevPos;
}

float PhysicsData::GetMass()
{
	return mass;
}

float PhysicsData::GetDrag()
{
	return drag;
}
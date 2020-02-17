#include "Physics.h"
#include "../Objects/GameObject.h"
#include "../Objects/SmartPointer.h"
#include "../Types/Point2D.h"

Physics::Physics()
{
	collidables = std::vector<collidable>();
}

void Physics::AddCollidableObject(SmartPointer<GameObject> newObj, float mass, float kd)
{
	collidables.push_back(collidable(WeakPointer<GameObject>(newObj), mass, kd));
}

void Physics::RunPhysics(float dt_ms)
{
	for(int i = 0; i < collidables.size(); i++)
	{
		//TODO: Figure out how to pass forces to physics... Soon?
		calcNewPos(dt_ms, collidables[i], Point2D(0, 1));
	}
}


void Physics::calcNewPos(float dt_ms, collidable colliData, Point2D forces)
{
	Point2D currPos = *(colliData.obj->GetPoint());
	Point2D prevPos = colliData.prevPoint;
	float mass = colliData.mass;
	float drag = colliData.kd;

	Point2D newPos = (currPos * (2.0f - drag)) - prevPos + ((forces / mass) * dt_ms) / 1000.0f;

	colliData.prevPoint = newPos;
}

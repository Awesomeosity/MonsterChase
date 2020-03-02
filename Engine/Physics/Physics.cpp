#include "Physics.h"
#include "../Objects/GameObject.h"
#include "../Objects/SmartPointer.h"
#include "../Types/Point2D.h"
Physics::Physics()
{
	InitializeCriticalSection(&queueModification);
}

Physics::~Physics()
{
	for (size_t i = 0; i < collidables.size(); i++)
	{
		collidables[i]->obj.Reset();
	}

}

void Physics::AddCollidableObject(WeakPointer<GameObject> newObj, float mass, float kd)
{
	EnterCriticalSection(&queueModification);
	SmartPointer<collidable> newCollid = SmartPointer<collidable>(new collidable(WeakPointer<GameObject>(newObj), mass, kd));
	collidables.push_back(newCollid);
	LeaveCriticalSection(&queueModification);
}

void Physics::RunPhysics(float dt_ms)
{
	Point2D force;
	switch (currKey)
	{
		//W
	case 87:
		force = Point2D(0, 10);
		break;
		//S
	case 83:
		force = Point2D(0, -10);
		break;
		//A
	case 65:
		force = Point2D(-10, 0);
		break;
		//D
	case 68:
		force = Point2D(10, 0);
		break;
	case 81:
		break;
		//No key being held down.
	case 0:
	default:
		force = Point2D(0, 0);
		break;
	}

	for(size_t i = 0; i < collidables.size(); i++)
	{
		//TODO: Figure out how to pass forces to physics... Soon?
		calcNewPos(dt_ms, *(collidables[i]), force);
	}
}


void Physics::calcNewPos(float dt_ms, collidable& colliData, Point2D forces)
{
	Point2D currPos = colliData.obj->GetPoint();
	Point2D prevPos = colliData.prevPoint;
	float mass = colliData.mass;
	//float drag = colliData.kd;

	Point2D newPos = (currPos * 2.0f) - prevPos + ((forces / mass) * dt_ms) / 1000.0f;

	colliData.obj->SetPoint(newPos);

	float currX = currPos.GetX();
	float currY = currPos.GetY();
	colliData.prevPoint.SetX(currX);
	colliData.prevPoint.SetY(currY);
}

void Physics::Dispose()
{
	for (size_t i = 0; i < collidables.size(); i++)
	{
		collidables[i]->obj.Reset();
		collidables[i].Reset();
	}

	collidables.clear();
}

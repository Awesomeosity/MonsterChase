#include "Physics.h"
#include "../Objects/GameObject.h"
#include "../Objects/SmartPointer.h"
#include "../Types/Point2D.h"
#include "../Types/Matrix4.h"
#include "../Types/Vector4.h"

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

void Physics::AddCollidableObject(WeakPointer<GameObject> newObj, float bound_X, float bound_Y, float mass, float kd)
{
	EnterCriticalSection(&queueModification);
	SmartPointer<collidable> newCollid = SmartPointer<collidable>(new collidable(WeakPointer<GameObject>(newObj), bound_X, bound_Y, mass, kd));
	collidables.push_back(newCollid);
	LeaveCriticalSection(&queueModification);
}

void Physics::RunPhysics(float dt_ms)
{
	for (size_t i = 0; i < collidables.size(); i++)
	{
		void* voidPtr = collidables[i]->obj->GetComponent("Forces");
		if (voidPtr == nullptr)
		{
			calcNewPos(dt_ms, *(collidables[i]), Point2D(0, 0));
		}
		else
		{
			Point2D* forcePtr = reinterpret_cast<Point2D*>(voidPtr);
			calcNewPos(dt_ms, *(collidables[i]), *forcePtr);
		}
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

void Physics::collisionCheck(collidable& object1, collidable& object2)
{
	Point2D A_Center = object1.obj->GetPoint();
	Point2D B_Center = object2.obj->GetPoint();
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

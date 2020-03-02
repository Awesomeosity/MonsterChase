#include "World.h"
#include "GameObject.h"
#include "SmartPointer.h"
#include "WeakPointer.h"
#include "../Types/Point2D.h"
World::World()
{
	InitializeCriticalSection(&queueModification);
}

World::~World()
{
	for(size_t i = 0; i < allObjects.size(); i++)
	{
		allObjects[i].Reset();
	}

	allObjects.clear();
}

WeakPointer<GameObject> World::AddObject()
{
	SmartPointer<GameObject> newObjPtr = SmartPointer<GameObject>(new GameObject());
	EnterCriticalSection(&queueModification);
	allObjects.push_back(newObjPtr);
	LeaveCriticalSection(&queueModification);

	return WeakPointer<GameObject>(newObjPtr);
}

WeakPointer<GameObject> World::AddObject(Point2D pt)
{
	SmartPointer<GameObject> newObjPtr = SmartPointer<GameObject>(new GameObject(pt));
	EnterCriticalSection(&queueModification);
	allObjects.push_back(newObjPtr);
	LeaveCriticalSection(&queueModification);

	return WeakPointer<GameObject>(newObjPtr);
}

void World::Dispose(WeakPointer<GameObject> ptr)
{
}


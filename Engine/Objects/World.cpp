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
		allObjects[i]->obj.Reset();
		allObjects[i].Reset();
	}

	allObjects.clear();
}

WeakPointer<GameObject> World::AddObject(std::string name)
{
	SmartPointer<GameObject> newObjPtr = SmartPointer<GameObject>(new GameObject());
	SmartPointer<objRef> newRef(new objRef(newObjPtr, name));
	EnterCriticalSection(&queueModification);
	allObjects.push_back(newRef);
	LeaveCriticalSection(&queueModification);

	return WeakPointer<GameObject>(newObjPtr);
}

WeakPointer<GameObject> World::AddObject(Point2D pt, std::string name)
{
	SmartPointer<GameObject> newObjPtr = SmartPointer<GameObject>(new GameObject(pt));
	SmartPointer<objRef> newRef(new objRef(newObjPtr, name));
	EnterCriticalSection(&queueModification);
	allObjects.push_back(newRef);
	LeaveCriticalSection(&queueModification);

	return WeakPointer<GameObject>(newObjPtr);
}

WeakPointer<GameObject> World::GetObjectByName(std::string name)
{
	SmartPointer<objRef> retRef;
	for (SmartPointer<objRef> ref : allObjects)
	{
		if (ref->name == name)
		{
			retRef = ref;
		}
	}

	return WeakPointer<GameObject>(retRef->obj);
}

void World::Dispose(WeakPointer<GameObject> ptr)
{
}


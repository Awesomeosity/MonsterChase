#include "World.h"
#include "GameObject.h"
#include "SmartPointer.h"
#include "WeakPointer.h"
#include "../Types/Point2D.h"
World::World()
{
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
	allObjects.push_back(newObjPtr);
	return WeakPointer<GameObject>(newObjPtr);
}

WeakPointer<GameObject> World::AddObject(Point2D pt)
{
	SmartPointer<GameObject> newObjPtr = SmartPointer<GameObject>(new GameObject(pt));
	allObjects.push_back(newObjPtr);
	return WeakPointer<GameObject>(newObjPtr);
}

void World::Dispose(WeakPointer<GameObject> ptr)
{
}


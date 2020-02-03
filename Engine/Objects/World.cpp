#include "World.h"
#include "GameObject.h"
#include "SmartPointer.h"
#include "WeakPointer.h"
#include "../Types/Point2D.h"
World::World()
{
	allObjects = std::vector<SmartPointer<GameObject>>();
}

World::~World()
{
	for(int i = 0; i < allObjects.size(); i++)
	{
		allObjects[i].Reset();
	}
}

WeakPointer<GameObject> World::AddObject()
{
	SmartPointer<GameObject> newObjPtr = SmartPointer<GameObject>(new GameObject());
	allObjects.push_back(newObjPtr);
	return WeakPointer<GameObject>::makePointer(newObjPtr);
}

WeakPointer<GameObject> World::AddObject(Point2D pt)
{
	SmartPointer<GameObject> newObjPtr = SmartPointer<GameObject>(new GameObject(pt));
	allObjects.push_back(newObjPtr);
	return WeakPointer<GameObject>::makePointer(newObjPtr);
}

void World::Dispose(WeakPointer<GameObject> ptr)
{
	SmartPointer<GameObject> targ;
	auto it = allObjects.begin();
	for (; it != allObjects.end(); it++)
	{
		//cursed comparison
		if (&(**it) == &(*ptr))
		{
			break;
		}
	}

	targ = *it;
	targ.Reset();
	allObjects.erase(it);
}


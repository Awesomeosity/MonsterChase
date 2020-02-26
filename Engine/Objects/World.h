#pragma once
#include <vector>
#include "../Types/Point2D.h"
#include "SmartPointer.h"
#include "WeakPointer.h"
class GameObject;
class World
{
public:
	World();
	//Very unsafe to create multiple worlds...
	World(const World& world) = delete;
	World(World&& world) = delete;
	World& operator=(const World& world) = delete;
	World& operator=(World&& ptr) = delete;
	~World();

	//Adds an object to the world reference. This should be called to create any object.
	WeakPointer<GameObject> AddObject();
	WeakPointer<GameObject> AddObject(Point2D pt);

	//If called by any system, disposes the given object given by a weakpointer.
	void Dispose(WeakPointer<GameObject> ptr);
private:
	std::vector<SmartPointer<GameObject>> allObjects;
};


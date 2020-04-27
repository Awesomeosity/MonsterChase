#pragma once
#include <vector>
#include "../Types/Point2D.h"
#include "GameObject.h"
#include "SmartPointer.h"
#include "WeakPointer.h"
#include <Windows.h>

struct objRef
{
	SmartPointer<GameObject> obj;
	std::string name;
	objRef(SmartPointer<GameObject> _obj, std::string _name)
		: obj(_obj), name(_name)
	{

	}
};

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
	WeakPointer<GameObject> AddObject(std::string name);
	WeakPointer<GameObject> AddObject(Point2D pt, std::string name);

	WeakPointer<GameObject> GetObjectByName(std::string name);
	
	//If called by any system, disposes the given object given by a weakpointer.
	void Dispose(WeakPointer<GameObject> ptr);
private:
	std::vector<SmartPointer<objRef>> allObjects;
	mutable CRITICAL_SECTION queueModification;
};


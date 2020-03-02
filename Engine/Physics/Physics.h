#pragma once
#include <vector>
#include "../Objects/GameObject.h"
#include "../Objects/WeakPointer.h"
#include "../Types/Point2D.h"
#include <Windows.h>
template <class T>
class SmartPointer;

struct collidable
{
	WeakPointer<GameObject> obj;
	float mass;
	float kd;
	Point2D prevPoint;
	collidable(WeakPointer<GameObject> _obj, float _mass, float _kd)
		:obj(_obj), mass(_mass), kd(_kd), prevPoint(_obj->GetPoint().GetX(), _obj->GetPoint().GetY())
	{
		
	}
};

class Physics
{
public:
	Physics();
	~Physics();

	void AddCollidableObject(WeakPointer<GameObject> newObj, float mass, float kd);
	void RunPhysics(float dt_ms);
	static void calcNewPos(float dt_ms, collidable& data, Point2D forces);
	void Dispose();

	int currKey = 0;
private:
	std::vector<SmartPointer<collidable>> collidables;
	mutable CRITICAL_SECTION queueModification;
};


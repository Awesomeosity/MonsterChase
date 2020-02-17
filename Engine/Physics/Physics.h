#pragma once
#include <vector>
#include "../Objects/WeakPointer.h"
#include "../Types/Point2D.h"
template <class T>
class SmartPointer;
class GameObject;

struct collidable
{
	WeakPointer<GameObject> obj;
	float mass;
	float kd;
	Point2D prevPoint;
	collidable(WeakPointer<GameObject> _obj, float _mass, float _kd)
		:obj(_obj), mass(_mass), kd(_kd), prevPoint()
	{
		
	}
};

class Physics
{
public:
	Physics();

	void AddCollidableObject(SmartPointer<GameObject> newObj, float mass, float kd);
	void RunPhysics(float dt_ms);
	static void calcNewPos(float dt_ms, collidable data, Point2D forces);
private:
	std::vector<collidable> collidables;
};


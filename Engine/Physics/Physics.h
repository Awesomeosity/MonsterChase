#pragma once
#include <vector>
#include "../Objects/GameObject.h"
#include "../Objects/WeakPointer.h"
#include "../Types/Point2D.h"
#include "../Types/Vector4.h"
#include <Windows.h>
template <class T>
class SmartPointer;
struct collidable
{
	WeakPointer<GameObject> obj;
	float bounding_X;
	float bounding_Y;
	float mass;
	float kd;
	Point2D prevPoint;
	collidable(WeakPointer<GameObject> _obj, float X, float Y, float _mass, float _kd)
		:obj(_obj), bounding_X(X), bounding_Y(Y), mass(_mass), kd(_kd), prevPoint(_obj->GetPoint().GetX(), _obj->GetPoint().GetY() + Y)
	{
		
	}
};

struct CollisionPair
{
	float collisionTime;
	Vector4 collisionNormal;
	SmartPointer<collidable> collisionObjs[2];
};

class Physics
{
public:
	Physics();
	~Physics();

	void AddCollidableObject(WeakPointer<GameObject> newObj, float bound_X, float bound_Y, float mass, float kd);
	void RunPhysics(float dt_ms);
	static void calcNewPos(float dt_ms, collidable& data, Point2D forces);
	static bool collisionCheck(collidable& object1, collidable& object2, float dt_ms);
	void Dispose();

private:
	CollisionPair findEarliestCollision(float dt_ms, Vector4 collisionAxisX, Vector4 collisionAxisY);
	bool collisionCheck(collidable& object1, collidable& object2, float dt_ms, Vector4 collisionAxisX, Vector4 collisionAxisY, float& o_floatTime, Vector4& o_collisionNormal);
	static bool collisionHelper(collidable& object1, collidable& object2, float dt_ms, float& o_open, float& o_close);
	std::vector<SmartPointer<collidable>> collidables;
	mutable CRITICAL_SECTION queueModification;
};


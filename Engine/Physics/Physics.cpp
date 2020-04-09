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
	//TODO: Iterate through all collidable pairs, find earliest collision (if any)
	//If collision,
	//1) Progress Physics to that point
	//2) Resolve Collision by applying Conservation of Momentum & Reflection (if necessary)
	//Repeat until the timestep is complete
	//If there is time left over, progress physics using the remaining time.

	if (collidables.size() == 0)
	{
		return;
	}

	float temp_time = dt_ms;

	//Get universal axis of collision
	float* universalRotation = reinterpret_cast<float*>(collidables[0]->obj->GetComponent("Rotation"));
	Matrix4 universalAxis = Matrix4::GenerateRotationMatrix(*universalRotation);
	Vector4 uni_X = universalAxis.getRow(0);
	Vector4 uni_Y = universalAxis.getRow(1);

	CollisionPair earliestCollision = findEarliestCollision(temp_time, uni_X, uni_Y);
	while(FloatCalcs::relativeEquality(earliestCollision.collisionTime, temp_time))
	{
		//TODO: Move physics forward to earliest collision time
		//calcNewPos(earliestCollision.collisionTime);
		
		//TODO: Resolve collision somehow??
		//resolveCollision(earliestCollision);

		temp_time -= earliestCollision.collisionTime;
		earliestCollision = findEarliestCollision(temp_time, uni_X, uni_Y);
	}

	//TODO: Progress physics using remaining time
	//calcNewPos(temp_time);

	/*
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
	*/
}


void Physics::calcNewPos(float dt_ms, collidable& colliData, Point2D forces)
{
	Point2D currPos = colliData.obj->GetPoint();
	currPos.SetY(currPos.GetY() + colliData.bounding_Y);
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

bool Physics::collisionCheck(collidable& object1, collidable& object2, float dt_ms)
{
	float AB_Open = 0.0f;
	float AB_Close = 0.0f;
	float BA_Open = 0.0f;
	float BA_Close = 0.0f;

	if (!collisionHelper(object1, object2, dt_ms, AB_Open, AB_Close))
	{
		return false;
	}

	if (!collisionHelper(object2, object1, dt_ms, BA_Open, BA_Close))
	{
		return false;
	}
	
	float bestOpen = (AB_Open < BA_Open) ? AB_Open : BA_Open;
	float bestClose = (AB_Close > BA_Close) ? AB_Close : BA_Close;

	if (bestClose > bestOpen)
	{
		return false;
	}
	else
	{
		return true;
	}
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

CollisionPair Physics::findEarliestCollision(float dt_ms, Vector4 collisionAxisX, Vector4 collisionAxisY)
{
	CollisionPair earliestCollision;
	earliestCollision.collisionTime = dt_ms;

	for (size_t i = 0; i < collidables.size() - 1; i++)
	{
		for (size_t j = i + 1; j < collidables.size(); j++)
		{
			float* collisionTime = new float(0.0f);
			Vector4* collisionNormal = new Vector4();
			if (collisionCheck(*collidables[i], *collidables[j], dt_ms, collisionAxisX, collisionAxisY, *collisionTime, *collisionNormal))
			{
				if (*collisionTime < earliestCollision.collisionTime)
				{
					earliestCollision.collisionTime = *collisionTime;
					earliestCollision.collisionNormal = *collisionNormal;
					earliestCollision.collisionObjs[0] = collidables[i];
					earliestCollision.collisionObjs[1] = collidables[j];
				}
			}

			delete collisionTime;
			delete collisionNormal;
		}
	}

	return earliestCollision;
}

bool Physics::collisionCheck(collidable& object1, collidable& object2, float dt_ms, Vector4 collisionAxisX, Vector4 collisionAxisY, float& o_floatTime, Vector4& o_collisionNormal)
{
	//TODO Implement this
	return false;
}

bool Physics::collisionHelper(collidable& object1, collidable& object2, float dt_ms, float& o_open, float& o_close)
{
	//Setting up matrices
	Point2D A_Center = object1.obj->GetPoint();
	A_Center += Point2D(0.0f, object1.bounding_Y);
	Point2D B_Center = object2.obj->GetPoint();
	B_Center += Point2D(0.0f, object2.bounding_Y);

	float* A_Rot = reinterpret_cast<float*>(object1.obj->GetComponent("Rotation"));
	float* B_Rot = reinterpret_cast<float*>(object2.obj->GetComponent("Rotation"));

	assert(A_Rot != nullptr);
	assert(B_Rot != nullptr);

	Matrix4 M_AWorld = Matrix4::GenerateTransformMatrix(A_Center.GetX(), A_Center.GetY(), 0.0f) * Matrix4::GenerateRotationMatrix(*A_Rot);
	Matrix4 M_BWorld = Matrix4::GenerateTransformMatrix(B_Center.GetX(), B_Center.GetY(), 0.0f) * Matrix4::GenerateRotationMatrix(*B_Rot);

	Matrix4 M_WorldA = M_AWorld.GenerateInvert();
	Matrix4 M_WorldB = M_BWorld.GenerateInvert();

	Matrix4 M_AB = M_WorldB * M_AWorld;

	Vector4 V_ACenterB = M_AB * Vector4(A_Center, 0.0f, 1.0f);

	//Velocity
	Point2D AVelocity = A_Center - object1.prevPoint;
	Point2D BVelocity = B_Center - object2.prevPoint;

	Point2D VelARelB = AVelocity - BVelocity;

	Vector4 VelAB = M_AB * Vector4(VelARelB, 0.0f, 0.0f);

	Vector4 AExtB_X = M_AB * Vector4(object1.bounding_X, 0.0f);
	Vector4 AExtB_Y = M_AB * Vector4(0.0f, object1.bounding_Y);

	float AProjB_X = fabs(AExtB_X.GetX()) + fabs(AExtB_Y.GetX());
	float AProjB_Y = fabs(AExtB_X.GetY()) + fabs(AExtB_Y.GetY());

	float bestClose = 0.0f;
	float bestOpen = 0.0f;

	//Checking X Axis
	float ACenterB_X = V_ACenterB.GetX();
	float BCenter_X = B_Center.GetX();

	float BLeft_X = BCenter_X - object2.bounding_X - AProjB_X;
	float BRight_X = BCenter_X + object2.bounding_X + AProjB_X;

	if (FloatCalcs::isZero(VelAB.GetX()))
	{
		//Handle 0 Velocity edge case
		if ((ACenterB_X < BLeft_X) || (ACenterB_X > BRight_X))
		{
			return false;
		}
	}
	else
	{
		float DOpen = BRight_X - ACenterB_X;
		float DClosed = BLeft_X - ACenterB_X;

		float tClose = DClosed / VelAB.GetX();
		float tOpen = DOpen / VelAB.GetX();

		//Switch the values if not expected
		if (tOpen < tClose)
		{
			float temp = tOpen;
			tOpen = tClose;
			tClose = temp;
		}

		//Catching guaranteed noncollision next frame
		if (tClose > dt_ms / 1000)
		{
			return false;
		}

		//Catching guaranteed noncollision from previous frame
		if (tClose < 0)
		{
			return false;
		}

		//Comparing tClose and tOpen
		bestClose = tClose;
		bestOpen = tOpen;
	}

	//Checking Y Axis
	float ACenterB_Y = V_ACenterB.GetY();
	float BCenter_Y = B_Center.GetY();

	float BLeft_Y = BCenter_Y - object2.bounding_Y - AProjB_Y;
	float BRight_Y = BCenter_Y + object2.bounding_Y + AProjB_Y;

	if (FloatCalcs::isZero(VelAB.GetY()))
	{
		//Handle 0 Velocity edge case
		if ((ACenterB_Y < BLeft_Y) || (ACenterB_Y > BRight_Y))
		{
			return false;
		}
	}
	else
	{
		float DOpen = BRight_Y - ACenterB_Y;
		float DClosed = BLeft_Y - ACenterB_Y;

		float tClose = DClosed / VelAB.GetY();
		float tOpen = DOpen / VelAB.GetY();

		//Switch the values if not expected
		if (tOpen < tClose)
		{
			float temp = tOpen;
			tOpen = tClose;
			tClose = temp;
		}

		//Catching guaranteed noncollision next frame
		if (tClose > dt_ms / 1000)
		{
			return false;
		}

		//Catching guaranteed noncollision from previous frame
		if (tClose < 0)
		{
			return false;
		}

		//Comparing tClose and tOpen
		bestClose = (tClose > bestClose || FloatCalcs::isZero(bestClose)) ? tClose : bestClose;
		bestOpen = (tOpen < bestOpen || FloatCalcs::isZero(bestOpen)) ? tOpen : bestOpen;
	}

	o_close = bestClose;
	o_open = bestOpen;

	return true;
}

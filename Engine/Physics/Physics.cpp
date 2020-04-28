#include "Physics.h"
#include "../Objects/GameObject.h"
#include "../Objects/SmartPointer.h"
#include "../Types/Point2D.h"
#include "../Types/Matrix4.h"
#include "../Types/Vector4.h"

//bruh
const float PI = 3.14159265358979323846f;

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

void Physics::AddCollidableObject(WeakPointer<GameObject> newObj, float bound_X, float bound_Y, float mass, float kd, int type)
{
	EnterCriticalSection(&queueModification);
	SmartPointer<collidable> newCollid = SmartPointer<collidable>(new collidable(WeakPointer<GameObject>(newObj), bound_X, bound_Y, mass, kd, type));
	collidables.push_back(newCollid);
	LeaveCriticalSection(&queueModification);
}

void Physics::RunPhysics(float dt_ms)
{
	//OutputDebugStringA("DEBUG: Starting Physics ticks.\n");

	if (collidables.size() == 0)
	{
		return;
	}

	float temp_time = dt_ms;
	

	//Get universal axis of collision
	float* universalRotation = reinterpret_cast<float*>(collidables[0]->obj->GetComponent("Rotation"));
	Matrix4 universalAxis = Matrix4::GenerateRotationMatrix(*universalRotation);
	Vector4 uni_X = universalAxis.getCol(0);
	Vector4 uni_Y = universalAxis.getCol(1);

	CollisionPair earliestCollision = findEarliestCollision(temp_time, uni_X, uni_Y);
	while(!FloatCalcs::relativeEquality(earliestCollision.collisionTime, temp_time))
	{
		//Progress physics to collision time
		calcAllPos(earliestCollision.collisionTime);

		//TODO: Resolve collision somehow??
		resolveCollision(earliestCollision);

		temp_time -= earliestCollision.collisionTime;
		earliestCollision = findEarliestCollision(temp_time, uni_X, uni_Y);
	}

	//Progress physics using remaining time
	calcAllPos(temp_time);
}


void Physics::calcNewPos(float dt_ms, collidable& colliData, Point2D forces)
{
	float* A_Rot = reinterpret_cast<float*>(colliData.obj->GetComponent("Rotation"));
	assert(A_Rot != nullptr);

	Point2D currPos = colliData.obj->GetPoint();
	currPos += Point2D(colliData.bounding_Y * sin(*A_Rot * PI / 180.0f), colliData.bounding_Y * cos(*A_Rot * PI / 180.0f));
	Point2D velocity_0 = colliData.velocity;
	float mass = colliData.mass;

	Point2D velocity_1 = velocity_0 + ((forces / mass) * (dt_ms / 1000.0f));

	Point2D newPos = currPos + ((velocity_0 + velocity_1) / 2.0) * (dt_ms / 1000.0f);

	//Readjust pos to correct position for sprite positioning
	newPos -= Point2D(colliData.bounding_Y * sin(*A_Rot * PI / 180.0f), colliData.bounding_Y * cos(*A_Rot * PI / 180.0f));

	colliData.obj->SetPoint(newPos);

	colliData.velocity.SetX(velocity_1.GetX());
	colliData.velocity.SetY(velocity_1.GetY());
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

void Physics::setVelocity(Point2D newVelocity, SmartPointer<GameObject> objRef)
{
	SmartPointer<collidable> targCollidable;
	for (SmartPointer<collidable> currCollid : collidables)
	{
		if (currCollid->obj == objRef)
		{
			targCollidable = currCollid;
		}
	}

	if (targCollidable->obj == nullptr)
	{
		return;
	}

	targCollidable->velocity = newVelocity;
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

	if (collidables.size() <= 1)
	{
		return earliestCollision;
	}

	for (size_t i = 0; i < collidables.size() - 1; i++)
	{
		for (size_t j = i + 1; j < collidables.size(); j++)
		{
			//ignore collisions between non-movables.
			if (collidables[i]->type == 1 || collidables[j]->type == 1)
			{
				float* collisionTime = new float(0.0f);
				Vector4* collisionNormalA = new Vector4();
				Vector4* collisionNormalB = new Vector4();
				bool collided = collisionCheck(*collidables[i], *collidables[j], dt_ms, collisionAxisX, collisionAxisY, *collisionTime, *collisionNormalA, *collisionNormalB);
				if (collided)
				{
					const size_t	lenBuffer = 65;
					char			Buffer[lenBuffer];

					sprintf_s(Buffer, lenBuffer, "DEBUG: Found collision at %2.5f milliseconds.\n", dt_ms);
					OutputDebugStringA(Buffer);

					if (*collisionTime < earliestCollision.collisionTime)
					{
						earliestCollision.collisionTime = *collisionTime;
						earliestCollision.collisionNormalA = *collisionNormalA;
						earliestCollision.collisionNormalB = *collisionNormalB;
						earliestCollision.collisionObjs[0] = collidables[i];
						earliestCollision.collisionObjs[1] = collidables[j];
					}
				}

				delete collisionTime;
				delete collisionNormalA;
				delete collisionNormalB;

			}
		}
	}

	return earliestCollision;
}

bool Physics::collisionCheck(collidable& object1, collidable& object2, float dt_ms, Vector4 collisionAxisX, Vector4 collisionAxisY, float& o_floatTime, Vector4& o_collisionNormalA, Vector4& o_collisionNormalB)
{
	float* A_Rot = reinterpret_cast<float*>(object1.obj->GetComponent("Rotation"));
	float* B_Rot = reinterpret_cast<float*>(object2.obj->GetComponent("Rotation"));
	assert(A_Rot != nullptr);
	assert(B_Rot != nullptr);

	//Adjust centers to match true center
	Point2D A_Center = object1.obj->GetPoint();
	A_Center += Point2D(object1.bounding_Y * sin(*A_Rot * PI / 180.0f), object1.bounding_Y * cos(*A_Rot * PI / 180.0f));
	Point2D B_Center = object2.obj->GetPoint();
	B_Center += Point2D(object2.bounding_Y * sin(*B_Rot * PI / 180.0f), object2.bounding_Y * cos(*B_Rot * PI / 180.0f));

	Matrix4 ARotation = Matrix4::GenerateRotationMatrix(*A_Rot);
	Matrix4 BRotation = Matrix4::GenerateRotationMatrix(*B_Rot);

	Point2D AVelocity = object1.velocity;
	Point2D BVelocity = object2.velocity;

	float bestClose = 0.0f;
	float bestOpen = dt_ms / 1000;

	//X Axis
	{
		float ACenterWorldX = Vector4::dotProd(collisionAxisX, Vector4(A_Center, 0.0f, 0.0f));
		float BCenterWorldX = Vector4::dotProd(collisionAxisX, Vector4(B_Center, 0.0f, 0.0f));

		float AExtWorldX = Vector4::dotProd(collisionAxisX, (ARotation.getCol(0).Normalize() * object1.bounding_X)) + Vector4::dotProd(collisionAxisX, (ARotation.getCol(1).Normalize() * object1.bounding_Y));
		float BExtWorldX = Vector4::dotProd(collisionAxisX, (BRotation.getCol(0).Normalize() * object2.bounding_X)) + Vector4::dotProd(collisionAxisX, (BRotation.getCol(1).Normalize() * object2.bounding_Y));

		float AVelWorldX = Vector4::dotProd(collisionAxisX, Vector4(AVelocity, 0.0f, 0.0f));
		float BVelWorldX = Vector4::dotProd(collisionAxisX, Vector4(BVelocity, 0.0f, 0.0f));

		float BExtX = AExtWorldX + BExtWorldX;
		float BLeftX = BCenterWorldX - BExtX;
		float BRightX = BCenterWorldX + BExtX;

		if (FloatCalcs::isZero(AVelWorldX - BVelWorldX))
		{
			//Handle 0 Velocity edge case
			if ((ACenterWorldX < BLeftX) || (ACenterWorldX > BRightX))
			{
				return false;
			}
		}
		else
		{
			float DClose = BLeftX - ACenterWorldX;
			float DOpen = BRightX - ACenterWorldX;

			float tClose = DClose / (AVelWorldX - BVelWorldX);
			float tOpen = DOpen / (AVelWorldX - BVelWorldX);

			bool swapped = false;

			//Swap if velocity is going in opposite direction
			if (tOpen < tClose)
			{
				float tempTime = tOpen;
				tOpen = tClose;
				tClose = tempTime;
				swapped = true;
			}

			if (tClose * 1000 > dt_ms)
			{
				return false;
			}

			if (tOpen < 0)
			{
				return false;
			}

			bestClose = tClose > bestClose ? tClose : bestClose;
			bestOpen = tOpen < bestOpen ? tOpen : bestOpen;

			if (ACenterWorldX - BCenterWorldX >= 0)
			{
				o_collisionNormalA = collisionAxisX;
				o_collisionNormalB = -collisionAxisX;
			}
			else
			{
				o_collisionNormalA = -collisionAxisX;
				o_collisionNormalB = collisionAxisX;
			}
		}
	}

	//Y Axis
	{
		float ACenterWorldX = Vector4::dotProd(collisionAxisY, Vector4(A_Center, 0.0f, 0.0f));
		float BCenterWorldX = Vector4::dotProd(collisionAxisY, Vector4(B_Center, 0.0f, 0.0f));

		float AExtWorldX = Vector4::dotProd(collisionAxisY, (ARotation.getCol(0).Normalize() * object1.bounding_X)) + Vector4::dotProd(collisionAxisY, (ARotation.getCol(1).Normalize() * object1.bounding_Y));
		float BExtWorldX = Vector4::dotProd(collisionAxisY, (BRotation.getCol(0).Normalize() * object2.bounding_X)) + Vector4::dotProd(collisionAxisY, (BRotation.getCol(1).Normalize() * object2.bounding_Y));

		float AVelWorldX = Vector4::dotProd(collisionAxisY, Vector4(AVelocity, 0.0f, 0.0f));
		float BVelWorldX = Vector4::dotProd(collisionAxisY, Vector4(BVelocity, 0.0f, 0.0f));

		float BExtX = AExtWorldX + BExtWorldX;
		float BLeftX = BCenterWorldX - BExtX;
		float BRightX = BCenterWorldX + BExtX;

		if (FloatCalcs::isZero(AVelWorldX - BVelWorldX))
		{
			//Handle 0 Velocity edge case
			if ((ACenterWorldX < BLeftX) || (ACenterWorldX > BRightX))
			{
				return false;
			}
		}
		else
		{
			float DClose = BLeftX - ACenterWorldX;
			float DOpen = BRightX - ACenterWorldX;

			float tClose = DClose / (AVelWorldX - BVelWorldX);
			float tOpen = DOpen / (AVelWorldX - BVelWorldX);

			bool swapped = false;

			//Swap if velocity is going in opposite direction
			if (tOpen < tClose)
			{
				float tempTime = tOpen;
				tOpen = tClose;
				tClose = tempTime;
				swapped = true;
			}

			if (tClose * 1000 > dt_ms)
			{
				return false;
			}

			if (tOpen < 0)
			{
				return false;
			}

			if (bestClose < tClose)
			{
				bestClose = tClose;

				if (ACenterWorldX - BCenterWorldX >= 0)
				{
					o_collisionNormalA = collisionAxisY;
					o_collisionNormalB = -collisionAxisY;
				}
				else
				{
					o_collisionNormalA = -collisionAxisY;
					o_collisionNormalB = collisionAxisY;
				}
			}

			bestOpen = tOpen < bestOpen ? tOpen : bestOpen;
		}
	}

	if (bestClose > bestOpen)
	{
		return false;
	}
	else
	{
		o_floatTime = bestClose;
		return true;
	}
}

bool Physics::collisionHelper(collidable& object1, collidable& object2, float dt_ms, float& o_open, float& o_close)
{
	float* A_Rot = reinterpret_cast<float*>(object1.obj->GetComponent("Rotation"));
	float* B_Rot = reinterpret_cast<float*>(object2.obj->GetComponent("Rotation"));
	assert(A_Rot != nullptr);
	assert(B_Rot != nullptr);

	//Setting up matrices
	Point2D A_Center = object1.obj->GetPoint();
	A_Center += Point2D(object1.bounding_Y * sin(*A_Rot * PI / 180.0f), object1.bounding_Y * cos(*A_Rot * PI / 180.0f));
	Point2D B_Center = object2.obj->GetPoint();
	B_Center += Point2D(object2.bounding_Y * sin(*B_Rot * PI / 180.0f), object2.bounding_Y * cos(*B_Rot * PI / 180.0f));

	Matrix4 M_AWorld = Matrix4::GenerateTransformMatrix(A_Center.GetX(), A_Center.GetY(), 0.0f) * Matrix4::GenerateRotationMatrix(*A_Rot);
	Matrix4 M_BWorld = Matrix4::GenerateTransformMatrix(B_Center.GetX(), B_Center.GetY(), 0.0f) * Matrix4::GenerateRotationMatrix(*B_Rot);

	Matrix4 M_WorldA = M_AWorld.GenerateInvert();
	Matrix4 M_WorldB = M_BWorld.GenerateInvert();

	Matrix4 M_AB = M_WorldB * M_AWorld;

	Vector4 V_ACenterB = M_AB * Vector4(A_Center, 0.0f, 1.0f);

	//Velocity
	Point2D AVelocity = object1.velocity;
	Point2D BVelocity = object2.velocity;

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
		if (tClose * 1000 > dt_ms)
		{
			return false;
		}

		//Catching guaranteed noncollision from previous frame
		if (tOpen < 0)
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
		if (tClose * 1000 > dt_ms)
		{
			return false;
		}

		//Catching guaranteed noncollision from previous frame
		if (tOpen < 0)
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

void Physics::calcAllPos(float dt_ms)
{
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

}

void Physics::resolveCollision(CollisionPair collPair)
{
	//Both movable objs, conservation of momentum
	if (collPair.collisionObjs[0]->type == 1 && collPair.collisionObjs[1]->type == 1)
	{
		Point2D velocityA = collPair.collisionObjs[0]->velocity;
		Point2D velocityB = collPair.collisionObjs[1]->velocity;
		float massA = collPair.collisionObjs[0]->mass;
		float massB = collPair.collisionObjs[1]->mass;

		Point2D newVelocityA = ((massA - massB) / (massA + massB)) * velocityA + ((2 * massB) / (massA + massB)) * velocityB;
		Point2D newVelocityB = ((massB - massA) / (massB + massA)) * velocityB + ((2 * massA) / (massB + massA)) * velocityA;

		collPair.collisionObjs[0]->velocity = newVelocityA;
		collPair.collisionObjs[1]->velocity = newVelocityB;

	}

	//At least one non-movable obj, reflection on the movable object
	else if(collPair.collisionObjs[0]->type == 1 || collPair.collisionObjs[1]->type == 1)
	{
		Vector4 collisionNormal;
		if (collPair.collisionObjs[0]->type == 1)
		{
			collisionNormal = collPair.collisionNormalB.Normalize();
			Point2D oldVelocity = collPair.collisionObjs[0]->velocity;
			Vector4 newVelocity = Vector4(oldVelocity, 0.0f, 0.0f) - 2 * (Vector4::dotProd(Vector4(oldVelocity, 0.0f, 0.0f), collisionNormal)) * collisionNormal;
			Point2D newVelocityP(newVelocity.GetX(), newVelocity.GetY());
			collPair.collisionObjs[0]->velocity = newVelocityP;
		}
		else
		{
			collisionNormal = collPair.collisionNormalA.Normalize();
			Point2D oldVelocity = collPair.collisionObjs[1]->velocity;
			Vector4 newVelocity = Vector4(oldVelocity, 0.0f, 0.0f) - 2 * (Vector4::dotProd(Vector4(oldVelocity, 0.0f, 0.0f), collisionNormal)) * collisionNormal;
			Point2D newVelocityP(newVelocity.GetX(), newVelocity.GetY());
			collPair.collisionObjs[1]->velocity = newVelocityP;
		}
	}
}

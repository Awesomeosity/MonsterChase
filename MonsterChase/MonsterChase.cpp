// MonsterMash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <assert.h>
#include "Controllers/MonsterController.h"
#include "Controllers/PlayerController.h"
#include "Controllers/RandomController.h"
#include "conio.h"
#include <stdint.h>
#include <Windows.h>

#include "../Engine/Engine.cpp"
#include "../Engine/Timing/Timing.h"
#include "../Engine/Objects/GameObject.h"
#include "../Engine/Physics/PhysicsData.h"
#include "../Engine/Physics/Physics.h"
#include "../Engine/Physics/FloatCalcs.h"
#include "../Engine/Types/Matrix4.h"
#include "../Engine/Types/Point2D.h"
#include "../Engine/Objects/SmartPointer.h"
#include "../Engine/Objects/WeakPointer.h"
#include "../Engine/JobSystem/JobSystem.h"

#include <vector>

void SmPtrUnitTest()
{
	SmartPointer<int> smPtr_0 = SmartPointer<int>();
	assert(!smPtr_0.Peek());
	assert(smPtr_0.UseCount() == 0);
	assert(smPtr_0.WeakCount() == 0);

	int* testPtr_1 = new int();
	SmartPointer<int> smPtr_1 = SmartPointer<int>(testPtr_1);
	assert(smPtr_1.Peek());
	assert(smPtr_1.UseCount() == 1);
	assert(smPtr_1.WeakCount() == 0);

	{
		SmartPointer<int> smPtr_2 = SmartPointer<int>(smPtr_1);
		assert(smPtr_2.Peek());
		assert(smPtr_2.UseCount() == 2);
		assert(smPtr_2.WeakCount() == 0);
	}

	assert(smPtr_1.UseCount() == 1);
	assert(smPtr_1.Peek());

	SmartPointer<int> smPtr_3 = SmartPointer<int>(smPtr_1);
	assert(smPtr_1.UseCount() == 2);
	assert(smPtr_3.UseCount() == 2);

	smPtr_3.Reset();

	assert(smPtr_1.UseCount() == 1);

	assert(smPtr_1);

	SmartPointer<int> smPtr_4 = SmartPointer<int>(smPtr_1);
	SmartPointer<int> smPtr_5 = SmartPointer<int>(smPtr_4);

	assert(smPtr_1.UseCount() == 3);
	assert(smPtr_4.UseCount() == 3);
	assert(smPtr_5.UseCount() == 3);

	smPtr_4.Reset();
	assert(smPtr_1.UseCount() == 2);
	assert(smPtr_5.UseCount() == 2);

	assert(!smPtr_4.Peek());

	smPtr_5.Swap(smPtr_0);
	assert(smPtr_0.Peek());
	assert(smPtr_0.UseCount() == 2);
	assert(!smPtr_5.Peek());

	int* testPtr_2 = new int();
	SmartPointer<int> smPtr_7 = SmartPointer<int>(testPtr_2);

	assert(smPtr_1 == smPtr_0);
	assert(!(smPtr_1 == nullptr));
	assert(!(nullptr == smPtr_1));
	assert(smPtr_5 == nullptr);
	assert(nullptr == smPtr_5);

	assert(!(smPtr_1 == smPtr_7));

	assert(!(smPtr_1 != smPtr_0));
	assert(smPtr_1 != nullptr);
	assert(nullptr != smPtr_1);
	assert(!(smPtr_5 != nullptr));
	assert(!(nullptr != smPtr_5));

	assert(smPtr_1 != smPtr_7);

	//Weak Pointer test
	WeakPointer<int> wkPtr_0 = WeakPointer<int>(smPtr_5);
	WeakPointer<int> wkPtr_1 = WeakPointer<int>(smPtr_1);
	assert(wkPtr_1.WeakCount() == 1);
	assert(wkPtr_1.UseCount() == 2);

	SmartPointer<int> smPtr_6 = wkPtr_1.Promote();
	assert(wkPtr_1.UseCount() == 3);
	assert(wkPtr_1.WeakCount() == 1);
	assert(smPtr_6.UseCount() == 3);
	assert(smPtr_6.WeakCount() == 1);

	WeakPointer<int> wkPtr_2 = WeakPointer<int>(wkPtr_1);
	assert(wkPtr_2.WeakCount() == 2);
	assert(wkPtr_2.Peek());

	assert(wkPtr_2 == wkPtr_1);
	assert(wkPtr_2 == smPtr_6);
	assert(smPtr_6 == wkPtr_1);
	assert(!(wkPtr_2 == wkPtr_0));
	assert(!(wkPtr_0 == wkPtr_2));

	assert(!(wkPtr_2 != wkPtr_1));
	assert(!(wkPtr_2 != smPtr_6));
	assert(!(smPtr_6 != wkPtr_1));
	assert(wkPtr_2 != wkPtr_0);
	assert(wkPtr_0 != wkPtr_2);

	WeakPointer<int> wkPtr_3 = WeakPointer<int>(smPtr_7);

	assert(!(wkPtr_2 == wkPtr_3));
	assert(!(wkPtr_2 == smPtr_7));
	assert(!(smPtr_7 == wkPtr_1));
	assert(nullptr == wkPtr_0);
	assert(wkPtr_0 == nullptr);

	assert(wkPtr_2 != wkPtr_3);
	assert(wkPtr_2 != smPtr_7);
	assert(smPtr_7 != wkPtr_1);
	assert(!(nullptr != wkPtr_0));
	assert(!(wkPtr_0 != nullptr));


	wkPtr_1.Reset();
	assert(wkPtr_2.WeakCount() == 1);

	wkPtr_2.Swap(wkPtr_1);
	assert(!wkPtr_2.Peek());
	assert(wkPtr_1.WeakCount() == 1);
	assert(wkPtr_1.UseCount() == 3);

	wkPtr_1.Reset();

	assert(smPtr_6.UseCount() == 3);
	assert(smPtr_6.WeakCount() == 0);
}

void MatrixUnitTest()
{
	//Testing ctors
	Matrix4 m1 = Matrix4();
	assert(FloatCalcs::isZero(m1(0, 0)));
	assert(FloatCalcs::isZero(m1(0, 1)));
	assert(FloatCalcs::isZero(m1(0, 2)));
	assert(FloatCalcs::isZero(m1(0, 3)));

	assert(FloatCalcs::isZero(m1(1, 0)));
	assert(FloatCalcs::isZero(m1(1, 1)));
	assert(FloatCalcs::isZero(m1(1, 2)));
	assert(FloatCalcs::isZero(m1(1, 3)));

	assert(FloatCalcs::isZero(m1(2, 0)));
	assert(FloatCalcs::isZero(m1(2, 1)));
	assert(FloatCalcs::isZero(m1(2, 2)));
	assert(FloatCalcs::isZero(m1(2, 3)));

	assert(FloatCalcs::isZero(m1(3, 0)));
	assert(FloatCalcs::isZero(m1(3, 1)));
	assert(FloatCalcs::isZero(m1(3, 2)));
	assert(FloatCalcs::isZero(m1(3, 3)));

	m1(0, 0) = 1.0f;
	assert(FloatCalcs::relativeEquality(m1(0, 0), 1.0f));

	//Copy and assignment
	Matrix4 m2(m1);
	Matrix4 m3 = m1;

	assert(m1 == m2);
	assert(m2 == m3);
	assert(m3 == m1);

	//Vector and manual setup ctors
	Matrix4 m4(0.0f, 1.0f, 2.0f, 3.0f,
			   4.0f, 5.0f, 6.0f, 7.0f,
			   8.0f, 9.0f, 10.0f, 11.0f,
			   12.0f, 13.0f, 14.0f, 15.0f);

	Vector4 v1(0.0f, 4.0f, 8.0f, 12.0f);
	Vector4 v2(1.0f, 5.0f, 9.0f, 13.0f);
	Vector4 v3(2.0f, 6.0f, 10.0f, 14.0f);
	Vector4 v4(3.0f, 7.0f, 11.0f, 15.0f);

	Matrix4 m5(v1, v2, v3, v4);

	assert(m4 == m5);

	//Testing static functions
	Matrix4 m6(Matrix4::GenerateRotationMatrix(45.0f));
	Matrix4 m7(Matrix4::GenerateScalingMatrix(2.0f, 2.0f));
	//u wot m8
	Matrix4 m8(Matrix4::GenerateTransformMatrix(10.0f, 10.0f, 0.0f));

	//Operator testing
	Matrix4 m9 = m4;
	Matrix4 m10 = m4 + m5;
	m4 += m5;
	assert(m4 == m10);
	
	m4 -= m5;
	assert(m9 == m4);

	m4 *= 2.0f;
	assert(m4 == m10);
	Matrix4 m11 = m4 - m5;


	m4 /= 2.0f;
	assert(m4 == m9);
	assert(m11 == m4);

	Matrix4 m12 = m4 * 2;
	assert(m12 == m10);

	Matrix4 m13 = m12 / 2;
	assert(m13 == m11);

	Matrix4 m14 = 2 * m13;
	assert(m14 == m12);

	assert(m14 != m4);

	//Inversion and Transposition
	Matrix4 m15 = m6.GenerateInvert();
	m6.Invert();
	assert(m15 == m6);

	m15.Transpose();
	Matrix4 m16 = m6.GenerateTranspose();
	assert(m15 == m16);

	m15.Transpose();
	assert(m6 == m15);

	m15.Invert();
	m6.Invert();
	assert(m6 == m15);


	Matrix4 m18 = m8 * m6;
	Matrix4 m17 = Matrix4::GenerateHomogenous(10, 10, 45);
	assert(m18 == m17);

	Vector4 v5 = Vector4(2.0f, 0.0f);
	Vector4 v6 = m17 * v5;

	m17.Invert();
	Vector4 v7 = m17 * v6;
	assert(v7 == v5);

	_CrtDumpMemoryLeaks();
}

void CollisionUnitTest()
{
	//Phase 1: No Velocity
	//These should not collide
	SmartPointer<GameObject> ObjA = SmartPointer<GameObject>(new GameObject());
	ObjA->AddComponent("Rotation", new float(0.0f));
	collidable* collid_A = new collidable(WeakPointer<GameObject>(ObjA), 50, 50, 0.0, 0.0);
	SmartPointer<GameObject> ObjB = SmartPointer<GameObject>(new GameObject(500.0f, 500.0f));
	ObjB->AddComponent("Rotation", new float(0.0f));
	collidable* collid_B = new collidable(WeakPointer<GameObject>(ObjB), 50, 50, 0.0, 0.0);
	assert(!Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(0.0f, 500.0f);
	collid_B->velocity = Point2D(0.0f, 550.0f);
	assert(!Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(500.0f, 0.0f);
	collid_B->velocity = Point2D(500.0f, 50.0f);
	assert(!Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	//These should collide
	ObjB->SetPoint(0.0f, 25.0f);
	collid_B->velocity = Point2D(0.0f, 75.0f);
	assert(Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(25.0f, 0.0f);
	collid_B->velocity = Point2D(25.0f, 50.0f);
	assert(Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));
	
	ObjB->SetPoint(0.0f, 0.0f);
	collid_B->velocity = Point2D(0.0f, 50.0f);
	assert(Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	//Phase 2: Velocity
	//We manipulate velocity by setting the previous point of the collidable.
	ObjB->SetPoint(500.0f, 500.0f);
	collid_B->velocity = Point2D(450.0f, 550.0f); //Moving in X+
	assert(!Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(0.0f, 500.0f);
	collid_B->velocity = Point2D(0.0f, 600.0f); //Y-
	assert(!Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(0.0f, 500.0f);
	collid_B->velocity = Point2D(0.0f, 500.0f); //Y+
	assert(!Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(500.0f, 0.0f);
	collid_B->velocity = Point2D(450.0f, 50.0f); //X+
	assert(!Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(500.0f, 0.0f);
	collid_B->velocity = Point2D(550.0f, 50.0f); //X-
	assert(!Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	//These ones should collide
	ObjB->SetPoint(100.0f, 0.0f);
	collid_B->velocity = Point2D(200.0f, 50.0f); //X-
	assert(Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(0.0f, -100.0f);
	collid_B->velocity = Point2D(0.0f, -200.0f); //Y+
	assert(Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));

	ObjB->SetPoint(-100.0f, -100.0f);
	collid_B->velocity = Point2D(-200.0f, -200.0f); //X+, Y+
	assert(Physics::collisionCheck(*collid_A, *collid_B, 1000.0f));


	delete collid_A;
	delete collid_B;
	ObjA.Reset();
	ObjB.Reset();
}

void gameObjHandler(std::string i_fileName)
{
	int* controllerType = new int();
	WeakPointer<GameObject> newObj = Engine::CreateActor(i_fileName, *controllerType);
	assert(*controllerType != -1);

	//TODO set up controllers to add to AI Engine
	switch (*controllerType)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

	delete controllerType;
}

void makeGameObjs(std::vector < std::string > i_fileNames)
{
	Engine::JobSystem::CreateQueue("OBJMaker", 4);

	for (size_t i = 0; i < i_fileNames.size(); i++)
	{
		std::string fileName = i_fileNames[i];
		Engine::JobSystem::RunJob("OBJMaker", [fileName]() {
			OutputDebugStringA("DEBUG: Thread started.\n");
			gameObjHandler(fileName);
			OutputDebugStringA("DEBUG: Thread ended.\n");
		});
	}

	do
	{
		Sleep(10);
	} while (Engine::JobSystem::HasJobs("OBJMaker"));

	Engine::JobSystem::RequestShutdown();
	OutputDebugStringA("DEBUG: All threads complete.\n");
}


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc();
	//MatrixUnitTest();
	//CollisionUnitTest();
	{
		float playX = 10.0f;
		float playY = 10.0f;

		unsigned short ID = 65535;

		Engine::initEngine();
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Mash", ID, static_cast<unsigned int>(playX) * 50 * 2, static_cast<unsigned int>(playY) * 50 * 2);

		if (bSuccess)
		{
			OutputDebugStringA("DEBUG: bSuccess confirmed.\n");
		}
		else
		{
			OutputDebugStringA("DEBUG: bSuccess failed.\n");
		}


		std::vector < std::string > charArray;
		charArray.push_back("data\\Player.json");
		charArray.push_back("data\\Enemy.json");

		makeGameObjs(charArray);

		if (bSuccess)
		{
			Engine::Run();
		}

		charArray.clear();
	}
	_CrtDumpMemoryLeaks();
	OutputDebugStringA("DEBUG: ENGINE END.\n");
}
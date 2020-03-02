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

void gameObjHandler(const char* i_fileName)
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

void makeGameObjs(std::vector<const char*> i_fileNames)
{
	Engine::JobSystem::CreateQueue("OBJMaker", 4);

	for (size_t i = 0; i < i_fileNames.size(); i++)
	{
		const char* fileName = i_fileNames[i];
		Engine::JobSystem::RunJob("OBJMaker", [fileName]() {
			gameObjHandler(fileName);
		});
	}

	do
	{
		Sleep(10);
	} while (Engine::JobSystem::HasJobs("OBJMaker"));

	Engine::JobSystem::RequestShutdown();
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	_CrtSetBreakAlloc(216);

	{
		float playX = 10.0f;
		float playY = 10.0f;

		unsigned short ID = 65535;

		Engine::initEngine();
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Mash", ID, static_cast<unsigned int>(playX) * 50 * 2, static_cast<unsigned int>(playY) * 50 * 2);


		std::vector<const char*> charArray;
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

}
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
#include <vector>


void inline GetMonsterCount(unsigned int* const maxMonsters)
{
	//TEMP: Fixed Monster Count because no input lol
	*maxMonsters = 5;

	/*
	unsigned int monsterCount = 0;
	while (true)
	{
		std::cout << "Please enter the initial amount of monsters: ";
		std::cin >> monsterCount;

		if (std::cin.fail() || monsterCount > UINT_MAX - 10)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid input. Please try entering an positive integer.\n";
		}
		else
		{
			std::cin.ignore(INT_MAX, '\n');
			*maxMonsters = monsterCount;
			break;
		}
	}
	*/
}

bool inline CheckPlayer(PlayerController* const player, std::vector<MonsterController*>* monsters, std::vector<RandomController*>* randoms)
{
	float playerX = player->getPlayerPosition().GetX();
	float playerY = player->getPlayerPosition().GetY();

	for (size_t i = 0; i < (*monsters).size(); i++)
	{
		if ((*monsters)[i]->getActive() && (*monsters)[i]->getPosition().GetX() == playerX && (*monsters)[i]->getPosition().GetY() == playerY)
		{
			return false;
		}
	}
	for (size_t i = 0; i < (*randoms).size(); i++)
	{
		if ((*randoms)[i]->getActive() && (*randoms)[i]->getPosition().GetX() == playerX && (*randoms)[i]->getPosition().GetY() == playerY)
		{
			return false;
		}
	}

	return true;
}

void inline GameLoop(PlayerController* const player, const std::vector<IGameObjectController*>* controllers, std::vector<MonsterController*>* monsters, std::vector<RandomController*>* randoms)
{
	float beforePosX, beforePosY, afterPosX, afterPosY;
	bool isAlive = true;
	while (isAlive)
	{
		beforePosX = player->getPlayerPosition().GetX();
		beforePosY = player->getPlayerPosition().GetY();
		for (size_t i = 0; i < controllers->size(); i++)
		{
			(*controllers)[i]->UpdateGameObject();
			if (i == 0)
			{
				afterPosX = player->getPlayerPosition().GetX();
				afterPosY = player->getPlayerPosition().GetY();
				if (beforePosX == afterPosX && beforePosY == afterPosY)
				{
					//std::cout << "Quitting...\n";
					isAlive = false;
					break;
				}
				if (!CheckPlayer(player, monsters, randoms))
				{
					//std::cout << "You got hit!\n";
					isAlive = false;
					break;
				}
			}
		}

	}
}

inline GameObject* MonsterCreateLoop(const float playX, const float playY, unsigned int* const maxMonsters, GameObject* player, std::vector<IGameObjectController*>* controllers, std::vector<MonsterController*>* monsters, std::vector<RandomController*>* randoms)
{
	unsigned int i = 0;
	bool isActive = false;
	GetMonsterCount(maxMonsters);
	//std::cout << *maxMonsters << " is the initial amount of monsters.\n";
	GameObject* monsterObjs = new GameObject[*maxMonsters + 10];
	for (; i < *maxMonsters + 10; i++)
	{
		char* name = new char[256]();

		if (isActive)
		{
			//TEMP: Change this back when we get inputs
			//std::cout << "Please enter Monster #" << i - 9 << "'s name: ";
			//GetName(name);
		}
		else
		{
			char beginning[256] = "Monster #";
			char buffer[256];
			buffer[0] = '\0';
			_itoa_s(i, buffer, 10);
			strcat_s(beginning, buffer);
			strcpy_s(name, 256, beginning);
		}

		if (rand() / (RAND_MAX / 2) == 0)
		{
			//TEMP: Change this back when we get inputs
			strcpy_s(name, 256, "bruh");
			MonsterController* newController = new MonsterController(isActive, playX, playY, &(monsterObjs[i]), player, name);

			controllers->push_back(newController);
			monsters->push_back(newController);
		}
		else
		{
			RandomController* newController = new RandomController(isActive, playX, playY, &(monsterObjs[i]), name);
			controllers->push_back(newController);
			randoms->push_back(newController);
		}

		if (i == 9)
		{
			isActive = true;
		}
	}

	return monsterObjs;
}



void inline CreatePlayer(const float playX, const float playY, PlayerController* player, GameObject* playerObj)
{
	//TEMP: Change this back when we get inputs
	char* playerName = new char[256]();
	strcpy_s(playerName, 256, "bruh");
	//GetName(playerName);
	player->SetGameObject(playerObj);
	player->Setup(playerName, playX, playY);
}


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



int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc(265);

	{
		float playX = 10.0f;
		float playY = 10.0f;

		unsigned short ID = 65535;

		initEngine();
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Mash", ID, static_cast<unsigned int>(playX) * 50 * 2, static_cast<unsigned int>(playY) * 50 * 2);


		std::vector<const char*> charArray;
		char* chText = const_cast<char*>("data\\player.json");

		charArray.push_back(chText);
		for (size_t i = 0; i < charArray.size(); i++)
		{
			int* conType = new int();
			WeakPointer<GameObject> newObj = CreateActor(charArray[i], *conType);

			assert(*conType != -1);

			//TODO set up controllers to add to AI Engine
			switch (*conType)
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

			delete conType;
		}

		if (bSuccess)
		{
			Run();
		}

		charArray.clear();


	}
	_CrtDumpMemoryLeaks();
}

int main()
{
	float playX = 10.0f;
	float playY = 10.0f;
	unsigned int monsterCount = 0;
	unsigned int* maxMonsters = &monsterCount;
	Point2D* zero = new Point2D(0, 0);
	GameObject* playerObj = new GameObject(*zero);
	std::vector<IGameObjectController*>* controllers = new std::vector<IGameObjectController*>();
	std::vector<MonsterController*>* monsters = new std::vector<MonsterController*>();
	std::vector<RandomController*>* randoms = new std::vector<RandomController*>();

	PlayerController* player = new PlayerController();
	controllers->push_back(player);


	GameObject* generated = MonsterCreateLoop(playX, playY, maxMonsters, playerObj, controllers, monsters, randoms);
	CreatePlayer(playX, playY, player, playerObj);

	GameLoop(player, controllers, monsters, randoms);

	for (size_t i = 0; i < controllers->size(); i++)
	{
		delete (*controllers)[i];
	}
	delete controllers;
	delete monsters;
	delete randoms;
	delete playerObj;
	delete zero;
	delete[] generated;
	_CrtDumpMemoryLeaks();

#pragma warning (disable: 6031)
	_getch();
#pragma warning (disable: 6031)

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

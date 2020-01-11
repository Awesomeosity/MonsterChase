// MonsterMash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Controllers/MonsterController.h"
#include "Controllers/PlayerController.h"
#include "Controllers/RandomController.h"
#include "conio.h"
#include "../Engine/Types/Point2D.h"
#include "../Engine/Objects/GameObject.h"
#include "../Engine/Engine.cpp"
#include <vector>

void inline GetMonsterCount(unsigned int* const maxMonsters)
{
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
}

bool inline CheckPlayer(PlayerController* const player, std::vector<MonsterController*>* monsters, std::vector<RandomController*>* randoms)
{
	float playerX = player->getPlayerPosition()->GetX();
	float playerY = player->getPlayerPosition()->GetY();

	for (int i = 0; i < (*monsters).size(); i++)
	{
		if ((*monsters)[i]->getActive() && (*monsters)[i]->getPosition()->GetX() == playerX && (*monsters)[i]->getPosition()->GetY() == playerY)
		{
			return false;
		}
	}
	for (int i = 0; i < (*randoms).size(); i++)
	{
		if ((*randoms)[i]->getActive() && (*randoms)[i]->getPosition()->GetX() == playerX && (*randoms)[i]->getPosition()->GetY() == playerY)
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
		beforePosX = player->getPlayerPosition()->GetX();
		beforePosY = player->getPlayerPosition()->GetY();
		for (int i = 0; i < controllers->size(); i++)
		{
			(*controllers)[i]->UpdateGameObject();
			if (i == 0)
			{
				afterPosX = player->getPlayerPosition()->GetX();
				afterPosY = player->getPlayerPosition()->GetY();
				if (beforePosX == afterPosX && beforePosY == afterPosY)
				{
					std::cout << "Quitting...\n";
					isAlive = false;
					break;
				} 
				if (!CheckPlayer(player, monsters, randoms))
				{
					std::cout << "You got hit!\n";
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
	std::cout << *maxMonsters << " is the initial amount of monsters.\n";
	GameObject* monsterObjs = new GameObject[*maxMonsters + 10];
	for (; i < *maxMonsters + 10; i++)
	{
		float monX = std::round(rand() / (RAND_MAX / playX * 2) - playX);
		float monY = std::round(rand() / (RAND_MAX / playY * 2) - playY);
		char* name = new char[256]();

		if (isActive)
		{
			std::cout << "Please enter Monster #" << i - 9 << "'s name: ";
			GetName(name);
		}
		if (!isActive)
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
			MonsterController* newController = new MonsterController(isActive, monX, monY, &(monsterObjs[i]), player, name);
			controllers->push_back(newController);
			monsters->push_back(newController);
		}
		else
		{
			RandomController* newController = new RandomController(isActive, monX, monY, &(monsterObjs[i]), name);
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
	std::cout << "Please enter your name: ";
	char* playerName = new char[256]();
	GetName(playerName);
	player->SetGameObject(playerObj);
	player->Setup(playerName, playX, playY);
}

int main()
{
	Point2D* point = new Point2D();
	point->Point2D_UnitTest();
	float playX = 10.0f;
	float playY = 10.0f;
	unsigned int monsterCount = 0;
	unsigned int* maxMonsters = &monsterCount;
	std::cout << "Monster Mash by Kevin Le (u0916211)\n";
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

	std::cout << "Press any key to exit...\n";

	for (int i = 0; i < controllers->size(); i++)
	{
		delete (*controllers)[i];
	}
	delete controllers;
	delete monsters;
	delete randoms;
	delete playerObj;
	delete point;
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

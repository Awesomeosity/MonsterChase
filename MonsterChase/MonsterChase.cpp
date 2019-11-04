// MonsterMash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MonsterController.h"
#include "PlayerController.h"
#include "RandomController.h"
#include "conio.h"
#include "../Engine/Point2D.h"
#include "../Engine/GameObject.h"
#include "../Engine/Engine.cpp"
#include <vector>

void GetMonsterCount(unsigned int* const maxMonsters)
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
}

void inline GameLoop(PlayerController* const player, const std::vector<IGameObjectController*>* controllers, std::vector<MonsterController*>* monsters, std::vector<RandomController*>* randoms)
{
	float beforePosX, beforePosY, afterPosX, afterPosY;
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

void SpawnMonsters(Monster* const monsters, unsigned int* const maxMonsters, const float playX, const float playY)
{
	for (unsigned int i = 0; i < *maxMonsters + 10; i++)
	{
		if (monsters[i].DecayTime() == 0)
		{
			monsters[i].setInit(!monsters[i].isInit());
			if (monsters[i].isInit() == true)
			{
				float monX = rand() / (RAND_MAX / playX * 2.0f) - playX;
				float monY = rand() / (RAND_MAX / playY * 2.0f) - playY;
				monsters[i].GetPoint()->SetX(monX);
				monsters[i].GetPoint()->SetY(monY);
				char beginning[256] = "Monster #";
				char buffer[256];
				buffer[0] = '\0';
				_itoa_s(i, buffer, 10);
				strcat_s(beginning, buffer);
				monsters[i].SetName(beginning);
				monsters[i].SetTime();
				std::cout << monsters[i].GetName() << " has spawned!\n";
			}
			if (monsters[i].isInit() == false)
			{
				std::cout << monsters[i].GetName() << " died!\n";
				monsters[i].SetTime();
			}
		}
	}
}

bool CheckPlayer(Player* const player, Monster* const monsters, unsigned int* const maxMonsters)
{
	float playerX = player->GetPoint()->GetX();
	float playerY = player->GetPoint()->GetY();

	for (unsigned int i = 0; i < *maxMonsters + 10; i++)
	{
		if (monsters[i].isInit() && monsters[i].GetPoint()->GetX() == playerX && monsters[i].GetPoint()->GetY() == playerY)
		{
			return false;
		}
	}
	return true;
}

void GameLoop(Monster* const monsters, Player* const player, unsigned int* const maxMonsters, const float playX, const float playY)
{
	while (true)
	{
		MonsterPrint(monsters, maxMonsters);
		std::cout << player->GetName() << "'s (Player) current position is: [" << player->GetPoint()->GetX() << ", " << player->GetPoint()->GetY() << "].\n";
		char movement = MoveLoop();
		if (movement == 'q' || movement == 'Q')
		{
			std::cout << "Quitting game...\n";
			break;
		}
		MoveMonsters(maxMonsters, monsters, player);
		SpawnMonsters(monsters, maxMonsters, playX, playY);
		player->MovePlayerMain(movement, player, playX, playY);
		if (!CheckPlayer(player, monsters, maxMonsters))
		{
			std::cout << "You got hit and died...\n";
			break;
		}
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
	GameObject* playerObj = new GameObject(zero);
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

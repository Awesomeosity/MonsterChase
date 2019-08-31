// MonsterMash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Monster.h"
#include "Player.h"
#include "conio.h"
#include "../Engine/Point2D.h"
#include "../Engine/GameObject.h"

void GetMonsterCount(unsigned int* maxMonsters)
{
	unsigned int monsterCount = 0;
	while (true)
	{
		std::cout << "Please enter the initial amount of monsters: ";
		std::cin >> monsterCount;

		if (std::cin.fail() || monsterCount < 0 || monsterCount > UINT_MAX - 10)
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

void GetName(char* name)
{
	while (true)
	{
		std::cin.getline(name, 256);
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Invalid input. Please try entering a string.\n";
		}
		else
		{
			return;
		}
	}

}

void MonsterPrint(Monster* monsters, unsigned int* maxMonsters)
{
	for (unsigned int i = 0; i < *maxMonsters + 10; i++)
	{
		if (monsters[i].isInit())
		{
			int monX = monsters[i].GetX();
			int monY = monsters[i].GetY();
			char* monName = monsters[i].GetName();
			std::cout << monName << "'s current position is: [" << monX << ", " << monY << "].\n";
		}
	}

}

void MoveMonsters(unsigned int* maxMonsters, Monster* monsters, Player* player)
{
	for (unsigned int i = 0; i < *maxMonsters + 10; i++)
	{
		if (monsters[i].isInit())
		{
			monsters[i].MoveMonster(player->GetPoint().GetX(), player->GetPoint().GetY());
		}
	}
}

void MovePlayer(char move, Player* player)
{
	if (move == 'W' || move == 'w')
	{
		int Y = player->GetPoint().GetY();
		player->GetPoint().SetY(++Y);
	}
	if (move == 'A' || move == 'a')
	{
		int X = player->GetPoint().GetX();
		player->GetPoint().SetX(--X);
	}
	if (move == 'S' || move == 's')
	{
		int Y = player->GetPoint().GetY();
		player->GetPoint().SetY(--Y);
	}
	if (move == 'D' || move == 'd')
	{
		int X = player->GetPoint().GetX();
		player->GetPoint().SetY(++X);
	}
}


void MovePlayerMain(char movement, Player* player, const int playX, const int playY)
{
	MovePlayer(movement, player);
	//Make sure player wraps around
	if (player->GetPoint().GetX() > playX)
	{
		player->GetPoint().SetX(playX * -1);
	}

	if (player->GetPoint().GetX() < playX * -1)
	{
		player->GetPoint().SetX(playX);
	}

	if (player->GetPoint().GetY() > playY)
	{
		player->GetPoint().SetY(playY * -1);
	}

	if (player->GetPoint().GetY() < playY * -1)
	{
		player->GetPoint().SetY(playY);
	}
}


char MoveLoop()
{
	char playerMove;
	while (true)
	{
		std::cout << "Please enter the direction you want to move in. W, A, S, D, 'Q' to quit.\n";
		playerMove = (char)_getch();

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cout << "Invalid input. Please try again.\n";
		}
		else
		{
			bool isValid = false;
			switch (playerMove)
			{
			case 'W':
			case 'w':
			case 'A':
			case 'a':
			case 'S':
			case 's':
			case 'D':
			case 'd':
			case 'q':
			case 'Q':
				isValid = true;
				break;
			default:
				break;
			}

			if (isValid)
			{
				return playerMove;
			}
			else
			{
				std::cout << "Invalid input. Please try again.\n";
			}

		}
	}
}

void SpawnMonsters(Monster* monsters, unsigned int* maxMonsters, const int playX, const int playY)
{
	for (unsigned int i = 0; i < *maxMonsters + 10; i++)
	{
		if (monsters[i].DecayTime() == 0)
		{
			monsters[i].setInit(!monsters[i].isInit());
			if (monsters[i].isInit() == true)
			{
				int monX = rand() / (RAND_MAX / playX * 2) - playX;
				int monY = rand() / (RAND_MAX / playY * 2) - playY;
				monsters[i].SetX(monX);
				monsters[i].SetY(monY);
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

bool CheckPlayer(Player* player, Monster* monsters, unsigned int* maxMonsters)
{
	int playerX = player->GetPoint().GetX();
	int playerY = player->GetPoint().GetY();

	for (unsigned int i = 0; i < *maxMonsters + 10; i++)
	{
		if (monsters[i].isInit() && monsters[i].GetX() == playerX && monsters[i].GetY() == playerY)
		{
			return false;
		}
	}
	return true;
}

void GameLoop(Monster* monsters, Player* player, unsigned int* maxMonsters, const int playX, const int playY)
{
	while (true)
	{
		MonsterPrint(monsters, maxMonsters);
		std::cout << player->GetName() << "'s (Player) current position is: [" << player->GetPoint().GetX() << ", " << player->GetPoint().GetY() << "].\n";
		char movement = MoveLoop();
		if (movement == 'q' || movement == 'Q')
		{
			std::cout << "Quitting game...\n";
			break;
		}
		MoveMonsters(maxMonsters, monsters, player);
		SpawnMonsters(monsters, maxMonsters, playX, playY);
		MovePlayerMain(movement, player, playX, playY);
		if (!CheckPlayer(player, monsters, maxMonsters))
		{
			std::cout << "You got hit and died...\n";
			break;
		}
	}
}

Monster* MonsterCreateLoop(int playX, int playY, unsigned int* maxMonsters)
{
	unsigned int i = 0;
	GetMonsterCount(maxMonsters);
	std::cout << *maxMonsters << " is the initial amount of monsters.\n";
	Monster* monsters = new Monster[*maxMonsters + 10];
	for (; i < *maxMonsters; i++)
	{
		int monX = rand() / (RAND_MAX / playX * 2) - playX;
		int monY = rand() / (RAND_MAX / playY * 2) - playY;
		std::cout << "Please enter Monster #" << i + 1 << "'s name: ";
		char name[256];
		GetName(name);
		monsters[i] = Monster(monX, monY, name);
	}
	for (; i < *maxMonsters + 10; i++)
	{
		monsters[i] = Monster();
	}
	return monsters;
}

Player* CreatePlayer(int playX, int playY)
{
	int playerX = rand() / (RAND_MAX / playX * 2) - playX;
	int playerY = rand() / (RAND_MAX / playY * 2) - playY;

	std::cout << "Please enter your name: ";
	char playerName[256];
	GetName(playerName);
	Player* player = new Player(Point2D(playerX, playerY), playerName);
	return player;
}

int main()
{
	static const int playX = 10;
	static const int playY = 10;
	unsigned int monsterCount = 0;
	unsigned int* maxMonsters = &monsterCount;
	int* const count = new int;
	std::cout << "Monster Mash by Kevin Le (u0916211)\n";
	Monster* monsters = MonsterCreateLoop(playX, playY, maxMonsters);
	Player* player = CreatePlayer(playX, playY);
	
	GameLoop(monsters, player, maxMonsters, playX, playY);

	std::cout << "Press any key to exit...\n";

	int ret = _getch();

	delete count;
	
	delete[] monsters;
	delete player;
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

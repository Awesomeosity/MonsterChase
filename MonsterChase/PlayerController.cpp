#include "PlayerController.h"
#include <iostream>
#include <conio.h>

PlayerController::PlayerController(GameObject* _player, char* _name, float _sizeX, float _sizeY)
	: player(_player), name(_name), maxX(_sizeX), maxY(_sizeY)
{
}

PlayerController::~PlayerController()
{
	delete[] name;
}

void PlayerController::Setup(char* playerName, float playX, float playY)
{
	name = playerName;
	maxX = playX;
	maxY = playY;
}

void PlayerController::SetGameObject(GameObject* object)
{
	player = object;
}

void PlayerController::UpdateGameObject()
{
	std::cout << name << "'s (Player) current position is: [" << player->GetPoint()->GetX() << ", " << player->GetPoint()->GetY() << "].\n";
	char direction = getMovement();
	float X = player->GetPoint()->GetX();
	float Y = player->GetPoint()->GetY();
	if (direction == 'W' || direction == 'w')
	{
		player->GetPoint()->SetY(++Y);
	}
	if (direction == 'A' || direction == 'a')
	{
		player->GetPoint()->SetX(--X);
	}
	if (direction == 'S' || direction == 's')
	{
		player->GetPoint()->SetY(--Y);
	}
	if (direction == 'D' || direction == 'd')
	{
		player->GetPoint()->SetX(++X);
	}
	boundCheck();
}

Point2D* PlayerController::getPlayerPosition() const
{
	return player->GetPoint();
}

char PlayerController::getMovement()
{
	while (true)
	{
		std::cout << "Please enter the direction you want to move in. W, A, S, D, 'Q' to quit.\n";
		char playerMove = (char)_getch();

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

void PlayerController::boundCheck()
{
	if (player->GetPoint()->GetX() > maxX)
	{
		player->GetPoint()->SetX(maxX * -1);
	}

	if (player->GetPoint()->GetX() < maxX * -1)
	{
		player->GetPoint()->SetX(maxX);
	}

	if (player->GetPoint()->GetY() > maxY)
	{
		player->GetPoint()->SetY(maxY * -1);
	}

	if (player->GetPoint()->GetY() < maxY * -1)
	{
		player->GetPoint()->SetY(maxY);
	}
}
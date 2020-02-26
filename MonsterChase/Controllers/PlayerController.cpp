#include "PlayerController.h"
#include <iostream>
#include <conio.h>
PlayerController::PlayerController()
	: player(nullptr), name(nullptr), maxX(0), maxY(0)
{
}

PlayerController::PlayerController(GameObject* i_player, char* i_name, float i_sizeX, float i_sizeY)
	: player(i_player), name(i_name), maxX(i_sizeX), maxY(i_sizeY)
{
}

PlayerController::~PlayerController()
{
	//delete[] name;
}

PlayerController::PlayerController(const PlayerController& i_controller) :
	player(i_controller.player), name(_strdup(i_controller.name)), maxX(i_controller.maxX), maxY(i_controller.maxY)
{

}

PlayerController::PlayerController(PlayerController&& i_controller) noexcept
	: player(nullptr), name(nullptr), maxX(0), maxY(0)
{
	player = i_controller.player;
	name = i_controller.name;
	maxX = i_controller.maxX;
	maxY = i_controller.maxY;

	i_controller.player = nullptr;
	i_controller.name = nullptr;
	i_controller.maxX = 0;
	i_controller.maxY = 0;

}

PlayerController& PlayerController::operator=(const PlayerController& i_other)
{
	if (this != &i_other)
	{
		player = i_other.player;
		name = _strdup(i_other.name);
		maxX = i_other.maxX;
		maxY = i_other.maxY;
	}
	return *this;
}

PlayerController& PlayerController::operator=(PlayerController&& i_other) noexcept
{
	if (this != &i_other)
	{
		delete player;
		delete name;
		
		player = i_other.player;
		name = i_other.name;
		maxX = i_other.maxX;
		maxY = i_other.maxY;

		i_other.player = nullptr;
		i_other.name = nullptr;
		i_other.maxX = 0;
		i_other.maxY = 0;
	}

	return *this;
}

void PlayerController::Setup(char* const i_playerName, const float i_playX, const float i_playY)
{
	name = i_playerName;
	maxX = i_playX;
	maxY = i_playY;
}

void PlayerController::SetGameObject(GameObject* const i_object)
{
	player = i_object;
}

void PlayerController::UpdateGameObject()
{
	//TEMP: Disabled for assignment 2.02
	/*
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
	*/
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
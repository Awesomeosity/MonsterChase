#include "Player.h"
#include <iostream>
#include <conio.h>

char Player::MoveLoop()
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

Player::Player(int X, int Y, char name[])
{
	_X = X;
	_Y = Y;
	_name = new char[strlen(name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(name) + 1), name);
}

Player::~Player()
{
	delete[] _name;
}

void Player::MovePlayer(char move)
{
	if (move == 'W' || move == 'w')
	{
		_Y++;
	}
	if (move == 'A' || move == 'a')
	{
		_X--;
	}
	if (move == 'S' || move == 's')
	{
		_Y--;
	}
	if (move == 'D' || move == 'd')
	{
		_X++;
	}
}

char* Player::GetName()
{
	return _name;
}

void Player::SetName(char name[])
{
	strcpy_s(_name, strlen(name), name);
}

int Player::GetX()
{
	return _X;
}

void Player::SetX(int X)
{
	_X = X;
}

int Player::GetY()
{
	return _Y;
}

void Player::SetY(int Y)
{
	_Y = Y;
}
#include "RandomController.h"
#include <cstdlib>
#include <iostream>
RandomController::RandomController()
	: deathTime(0), maxX(0), maxY(0), monster(nullptr), name(nullptr), isActive(false)
{
}

RandomController::RandomController(bool i_active, float i_x, float i_y, GameObject* i_monster, char* i_name)
	: maxX(i_x), maxY(i_y), monster(i_monster), name(i_name), isActive(i_active)
{
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;

	float monX = std::round(rand() / (RAND_MAX / maxX * 2) - maxX);
	float monY = std::round(rand() / (RAND_MAX / maxY * 2) - maxY);
	monster->GetPoint()->SetX(monX);
	monster->GetPoint()->SetY(monY);

}

RandomController::~RandomController()
{
	delete[] name;
}

RandomController::RandomController(const RandomController& i_controller):
	deathTime(i_controller.deathTime), maxX(i_controller.maxX), maxY(i_controller.maxY),
	monster(i_controller.monster), name(_strdup(i_controller.name)), isActive(i_controller.isActive)
{
}

RandomController::RandomController(RandomController&& i_controller) noexcept
	: deathTime(0), maxX(0), maxY(0),
	monster(nullptr), name(nullptr), isActive(false)
{
	deathTime = i_controller.deathTime;
	maxX = i_controller.maxX;
	maxY = i_controller.maxY;
	monster = i_controller.monster;
	name = i_controller.name;
	isActive = i_controller.isActive;
}

RandomController& RandomController::operator=(const RandomController& i_other)
{
	if (this != &i_other)
	{
		deathTime = i_other.deathTime;
		maxX = i_other.maxX;
		maxY = i_other.maxY;
		monster = i_other.monster;
		name = _strdup(i_other.name);
		isActive = i_other.isActive;
	}
	return *this;
}

RandomController& RandomController::operator=(RandomController&& i_other) noexcept
{
	if (this != &i_other)
	{
		delete monster;
		delete name;

		deathTime = i_other.deathTime;
		maxX = i_other.maxX;
		maxY = i_other.maxY;
		monster = i_other.monster;
		name = i_other.name;
		isActive = i_other.isActive;
	}
	return *this;
}

void RandomController::SetGameObject(GameObject* const i_object)
{
	monster = i_object;
}

void RandomController::UpdateGameObject()
{
	//TEMP: Disabled for Assignment 2.02
	/*
	if (isActive)
	{
		float x = monster->GetPoint()->GetX();
		float y = monster->GetPoint()->GetY();

		unsigned int result = (rand() / (RAND_MAX / 5));
		switch (result)
		{
		case 0:
			monster->GetPoint()->SetX(++x);
			break;
		case 1:
			monster->GetPoint()->SetX(--x);
			break;
		case 2:
			monster->GetPoint()->SetY(++y);
			break;
		case 3:
			monster->GetPoint()->SetY(--y);
			break;
		case 4:
		default:
			break;
		}
	}
	checkAndSetTime();
	*/
}

bool RandomController::getActive() const
{
	return isActive;
}

Point2D* RandomController::getPosition() const
{
	return monster->GetPoint();
}


void RandomController::checkAndSetTime()
{
	deathTime--;
	if (deathTime == 0)
	{
		isActive = !isActive;

		if (isActive)
		{
			float monX = std::round(rand() / (RAND_MAX / maxX * 2) - maxX);
			float monY = std::round(rand() / (RAND_MAX / maxY * 2) - maxY);
			monster->GetPoint()->SetX(monX);
			monster->GetPoint()->SetY(monY);
			std::cout << name << " has revived at [" << monX << ", " << monY << "]!\n";
		}
		if (!isActive)
		{
			std::cout << name << " has died.\n";
		}

		deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
	}

	else if (isActive)
	{
		std::cout << name << "'s current position is: [" << monster->GetPoint()->GetX() << ", " << monster->GetPoint()->GetY() << "].\n";
	}
}

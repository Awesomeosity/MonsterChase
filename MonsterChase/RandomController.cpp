#include "RandomController.h"
#include <cstdlib>
#include <iostream>
RandomController::RandomController()
	: deathTime(0), maxX(0), maxY(0), monster(nullptr), name(nullptr), isActive(false)
{
}

RandomController::RandomController(bool active, float x, float y, GameObject* _monster, char* _name)
	: maxX(x), maxY(y), monster(_monster), name(_name), isActive(active)
{
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
}

RandomController::~RandomController()
{
	delete[] name;
}

RandomController::RandomController(const RandomController& controller):
	deathTime(controller.deathTime), maxX(controller.maxX), maxY(controller.maxY),
	monster(controller.monster), name(_strdup(controller.name)), isActive(controller.isActive)
{
}

RandomController::RandomController(RandomController&& controller) noexcept
	: deathTime(0), maxX(0), maxY(0),
	monster(nullptr), name(nullptr), isActive(false)
{
	deathTime = controller.deathTime;
	maxX = controller.maxX;
	maxY = controller.maxY;
	monster = controller.monster;
	name = controller.name;
	isActive = controller.isActive;
}

RandomController& RandomController::operator=(const RandomController& other)
{
	if (this != &other)
	{
		deathTime = other.deathTime;
		maxX = other.maxX;
		maxY = other.maxY;
		monster = other.monster;
		name = _strdup(other.name);
		isActive = other.isActive;
	}
	return *this;
}

RandomController& RandomController::operator=(RandomController&& other) noexcept
{
	if (this != &other)
	{
		delete monster;
		delete name;

		deathTime = other.deathTime;
		maxX = other.maxX;
		maxY = other.maxY;
		monster = other.monster;
		name = other.name;
		isActive = other.isActive;
	}
	return *this;
}

void RandomController::SetGameObject(GameObject* object)
{
	monster = object;
}

void RandomController::UpdateGameObject()
{
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

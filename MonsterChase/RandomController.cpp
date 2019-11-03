#include "RandomController.h"
#include <cstdlib>
#include <iostream>

RandomController::RandomController(float x, float y, GameObject* _monster, char* _name, bool active)
	: maxX(x), maxY(y), monster(_monster), name(_name), isActive(active)
{
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
}

RandomController::~RandomController()
{
	delete name;
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

void RandomController::checkAndSetTime()
{
	deathTime--;
	if (deathTime == 0)
	{
		isActive = !isActive;

		if (isActive)
		{
			float monX = rand() / (RAND_MAX / maxX * 2.0f) - maxX;
			float monY = rand() / (RAND_MAX / maxY * 2.0f) - maxY;
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

#include "MonsterController.h"
#include <cstdlib>
#include <iostream>


MonsterController::MonsterController(bool active, float x, float y, GameObject* _monster, GameObject* _player)
	: isActive(active), maxX(x), maxY(y)  
{
}

void MonsterController::Setup(GameObject* _monster, GameObject* _player)
{
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
	SetGameObject(_monster);
	GetFocus(_player);
}

void MonsterController::SetGameObject(GameObject* object)
{
	monster = object;
}

void MonsterController::GetFocus(GameObject* object)
{
	player = object;
}

void MonsterController::UpdateGameObject()
{
	if (isActive)
	{
		float x = monster->GetPoint()->GetX();
		float y = monster->GetPoint()->GetY();
		float diffX = player->GetPoint->GetX() - x;
		float diffY = player->GetPoint->GetY() - y;

		if (diffX > 0)
		{
			monster->GetPoint()->SetX(++x);
		}
		else if (diffX < 0)
		{
			monster->GetPoint()->SetX(--x);
		}
		else if (diffY > 0)
		{
			monster->GetPoint()->SetY(++y);
		}
		else
		{
			monster->GetPoint()->SetY(--y);
		}
	}
	checkAndSetTime();
}

void MonsterController::checkAndSetTime()
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
			std::cout << monster->GetName() << " has revived at [" << monX << ", " << monY << "]!\n";
		}
		if (!isActive)
		{
			std::cout << monster->GetName() << " has died.\n";
		}

		deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
	}

	else if (isActive)
	{
		std::cout << monster->GetName() << "'s current position is: [" << monster->GetPoint()->GetX() << ", " << monster->GetPoint()->GetY() << "].\n";
	}
}

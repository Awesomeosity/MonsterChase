#include "MonsterController.h"
#include <cstdlib>
#include <iostream>

MonsterController::MonsterController(bool active, float x, float y, GameObject* _monster, GameObject* _player, char* _name)
	: isActive(active), maxX(x), maxY(y), monster(_monster), player(_player), name(_name)
{
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
}

MonsterController::~MonsterController()
{
	delete[] name;
}

MonsterController::MonsterController(const MonsterController& controller) :
	deathTime(controller.deathTime), maxX(controller.maxX), maxY(controller.maxY),
	monster(controller.monster), player(controller.player), name(_strdup(controller.name)),
	isActive(controller.isActive)
{
}

MonsterController& MonsterController::operator=(const MonsterController& other)
{
	if (this != &other)
	{
		deathTime = other.deathTime;
		maxX = other.maxX;
		maxY = other.maxY;
		monster = other.monster;
		player = other.player;
		name = _strdup(other.name);
		isActive = other.isActive;
	}
	return *this;
}

void MonsterController::Setup(bool active, float x, float y, GameObject* _monster, GameObject* _player, char* _name)
{
	isActive = active;
	maxX = x;
	maxY = y;
	monster = _monster;
	player = _player;
	name = _name;
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
		float diffX = player->GetPoint()->GetX() - x;
		float diffY = player->GetPoint()->GetY() - y;

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
		else if(diffY < 0)
		{
			monster->GetPoint()->SetY(--y);
		}
		else
		{

		}
	}
	checkAndSetTime();
}

bool MonsterController::getActive() const
{
	return isActive;
}

Point2D* MonsterController::getPosition() const
{
	return monster->GetPoint();
}

void MonsterController::checkAndSetTime()
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

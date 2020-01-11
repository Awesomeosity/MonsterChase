#include "MonsterController.h"
#include <cstdlib>
#include <iostream>

MonsterController::MonsterController()
	: maxX(0), maxY(0), monster(nullptr), player(nullptr), name(nullptr), isActive(false)
{
	deathTime = 0;
}

MonsterController::MonsterController(bool i_active, float i_x, float i_y, GameObject* i_monster, GameObject* i_player, char* i_name)
	: maxX(i_x), maxY(i_y), monster(i_monster), player(i_player), name(i_name), isActive(i_active)
{
	deathTime = (rand() / (RAND_MAX / maxTime)) + 1;
}

MonsterController::~MonsterController()
{
	delete[] name;
}

MonsterController::MonsterController(const MonsterController& i_controller) :
	deathTime(i_controller.deathTime), maxX(i_controller.maxX), maxY(i_controller.maxY),
	monster(i_controller.monster), player(i_controller.player), name(_strdup(i_controller.name)),
	isActive(i_controller.isActive)
{
}

MonsterController::MonsterController(MonsterController&& i_controller) noexcept
	: deathTime(0), maxX(0), maxY(0),
	monster(nullptr), player(nullptr), name(nullptr),
	isActive(false)
{
	deathTime = i_controller.deathTime;
	maxX = i_controller.maxX;
	maxY = i_controller.maxY;
	monster = i_controller.monster;
	player = i_controller.player;
	name = i_controller.name;
	isActive = i_controller.isActive;

	i_controller.deathTime = 0;
	i_controller.maxX = 0;
	i_controller.maxY = 0;
	i_controller.monster = nullptr;
	i_controller.player = nullptr;
	i_controller.name = nullptr;
	i_controller.isActive = false;
}

MonsterController& MonsterController::operator=(const MonsterController& i_other)
{
	if (this != &i_other)
	{
		deathTime = i_other.deathTime;
		maxX = i_other.maxX;
		maxY = i_other.maxY;
		monster = i_other.monster;
		player = i_other.player;
		name = _strdup(i_other.name);
		isActive = i_other.isActive;
	}
	return *this;
}

MonsterController& MonsterController::operator=(MonsterController&& i_other) noexcept
{
	if (this != &i_other)
	{
		delete monster;
		delete player;
		delete name;

		deathTime = i_other.deathTime;
		maxX = i_other.maxX;
		maxY = i_other.maxY;
		monster = i_other.monster;
		player = i_other.player;
		name = i_other.name;
		isActive = i_other.isActive;
	}

	return *this;
}

void MonsterController::Setup(const bool i_active, const float i_x, const float i_y, GameObject* const i_monster, GameObject* const i_player, char* const i_name)
{
	isActive = i_active;
	maxX = i_x;
	maxY = i_y;
	monster = i_monster;
	player = i_player;
	name = i_name;
}

void MonsterController::SetGameObject(GameObject* const i_object)
{
	monster = i_object;
}

void MonsterController::GetFocus(GameObject* const i_object)
{
	player = i_object;
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

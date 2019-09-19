#include "Monster.h"
#include <iostream>

Monster::Monster() : GameObject()
{
	_init = false;
	_toDie = rand() / (RAND_MAX / maxDuration) + 1;
}

Monster::Monster(Point2D point, char name[]) : GameObject(point, name)
{
	_init = true;
	_toDie = rand() / (RAND_MAX / maxDuration) + 1;
}

Monster::Monster(Monster& monster) : GameObject()
{
	SetName(monster.GetName());
	SetPoint(*(monster.GetPoint()));
	_init = monster._init;
	_toDie = monster._toDie;
}

Monster& Monster::operator=(Monster& monster)
{
	if (this == &monster)
	{
		return *this;
	}

	SetName(monster.GetName());
	SetPoint(*(monster.GetPoint()));
	_init = monster._init;
	_toDie = monster._toDie;
	return *this;
}

Monster::~Monster()
{
}

void Monster::MoveMonster(Point2D point)
{
	float x = GetPoint()->GetX();
	float y = GetPoint()->GetY();
	float diffX = point.GetX() - x;
	float diffY = point.GetY() - y;

	if (diffX > 0)
	{
		GetPoint()->SetX(++x);
	}
	else if (diffX < 0)
	{
		GetPoint()->SetX(--x);
	}
	else if (diffY > 0)
	{
		GetPoint()->SetX(++y);
	}
	else
	{
		GetPoint()->SetX(--y);
	}
}

bool Monster::isInit()
{
	return _init;
}

void Monster::setInit(bool init)
{
	_init = init;
}

int Monster::DecayTime()
{
	return --_toDie;
}

void Monster::SetTime()
{
	_toDie = (rand() / (RAND_MAX / maxDuration)) + 1;
}

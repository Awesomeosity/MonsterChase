#include "Monster.h"
#include <iostream>

Monster::Monster()
{
	_init = false;
	_X = 0;
	_Y = 0;
	_name = new char[1];
	_name[0] = '\n';
	_toDie = rand() / (RAND_MAX / maxDuration) + 1;
}

Monster::Monster(int X, int Y, char name[])
{
	_init = true;
	_name = new char[strlen(name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(name) + 1), name);
	_X = X;
	_Y = Y;
	_toDie = rand() / (RAND_MAX / maxDuration) + 1;
}

Monster::Monster(const Monster& monster)
{
	_init = monster._init;
	_X = monster._X;
	_Y = monster._Y;
	_name = new char[strlen(monster._name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(monster._name) + 1), monster._name);
	_toDie = monster._toDie;
}

Monster& Monster::operator=(const Monster& monster)
{
	if (this == &monster)
	{
		return *this;
	}

	_init = monster._init;
	_X = monster._X;
	_Y = monster._Y;
	_name = new char[strlen(monster._name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(monster._name) + 1), monster._name);
	_toDie = monster._toDie;
	return *this;
}

Monster::~Monster()
{
	delete[] _name;
}

void Monster::MoveMonster(int X, int Y)
{
	int diffX = X - _X;
	int diffY = Y - _Y;

	if (diffX > 0)
	{
		_X++;
	}
	else if (diffX < 0)
	{
		_X--;
	}
	else if (diffY > 0)
	{
		_Y++;
	}
	else
	{
		_Y--;
	}
}

char* Monster::GetName()
{
	return _name;
}

void Monster::SetName(char name[])
{
	_name = new char[strlen(name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(name) + 1), name);
}

int Monster::GetX()
{
	return _X;
}

void Monster::SetX(int X)
{
	_X = X;
}

int Monster::GetY()
{
	return _Y;
}

void Monster::SetY(int Y)
{
	_Y = Y;
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

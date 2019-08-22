#pragma once
#include <string>
class Monster
{
private:
	bool _init;
	char *_name;
	int _X;
	int _Y;
	int _toDie;
	const int maxDuration = 4;

public:
	Monster();
	Monster(int X, int Y, char name[]);
	Monster(const Monster& monster);
	Monster& operator=(const Monster& monster);
	~Monster();
	void MoveMonster(int X, int Y);
	char* GetName();

	void SetName(char name[]);

	int GetX();
	void SetX(int X);
	int GetY();
	void SetY(int Y);
	bool isInit();
	void setInit(bool init);
	int DecayTime();
	void SetTime();
};


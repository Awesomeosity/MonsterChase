#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Point2D.h"

class Monster : public GameObject
{
private:
	bool _init;
	int _toDie;
	const int maxDuration = 4;

public:
	Monster();
	Monster(Point2D point, char name[]);
	Monster(Monster& monster);
	Monster& operator=(Monster& monster);
	~Monster();

	void MoveMonster(Point2D);
	bool isInit();
	void setInit(bool init);
	int DecayTime();
	void SetTime();
};


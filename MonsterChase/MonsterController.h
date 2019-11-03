#pragma once
#include "..\Engine\IGameObjectController.h"
class MonsterController :
	public IGameObjectController
{
public:
	MonsterController(GameObject* monster);
	virtual void Move(Point2D point);
private:
	void checkAndSetTime();
	unsigned int deathTime;
	const unsigned int maxTime = 4;
	int maxX;
	int maxY;
	GameObject* monster;
	bool isActive;
};


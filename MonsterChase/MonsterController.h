#pragma once
#include "..\Engine\IGameObjectController.h"
class MonsterController :
	public IGameObjectController
{
public:
	MonsterController(GameObject* monster);
	virtual void Move(Point2D point);
	
private:
	GameObject* monster;
	bool isActive;
	unsigned int deathTime;
	const unsigned int maxTime = 4;
	void checkAndSetTime();
};


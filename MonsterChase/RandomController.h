#pragma once
#include "..\Engine\IGameObjectController.h"
#include <cstdlib>

class RandomController :
	public IGameObjectController
{
public:
	RandomController(GameObject* monster);
	virtual void Move();

private:
	GameObject* monster;
	bool isActive;
	unsigned int deathTime;
	const unsigned int maxTime = 4;
	void checkAndSetTime();
};


#pragma once
#include "../Engine/IGameObjectController.h"
class PlayerController :
	public IGameObjectController
{
public:
	PlayerController(GameObject* thisPlayer, int sizeX, int sizeY);
	virtual void Move(char direction);
private:
	GameObject* player;
	void boundCheck();
	int sizeX;
	int sizeY;
};


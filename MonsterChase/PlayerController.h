#pragma once
#include "../Engine/IGameObjectController.h"
class PlayerController :
	public IGameObjectController
{
public:
	PlayerController(GameObject* player, char* name, float _sizeX, float _sizeY);
	void SetGameObject(GameObject* object) override;
	void UpdateGameObject() override;
private:
	char getMovement();
	void boundCheck();
	GameObject* player;
	char* name;
	float maxX;
	float maxY;
};


#pragma once
#include "../Engine/IGameObjectController.h"
class PlayerController :
	public IGameObjectController
{
public:
	PlayerController(GameObject* player = nullptr, char* name = nullptr, float _sizeX = 0, float _sizeY = 0);
	~PlayerController();
	void Setup(char* playerName, float playX, float playY);
	void SetGameObject(GameObject* object) override;
	void UpdateGameObject() override;
	Point2D* getPlayerPosition() const;
private:
	char getMovement();
	void boundCheck();
	GameObject* player;
	char* name;
	float maxX;
	float maxY;
};


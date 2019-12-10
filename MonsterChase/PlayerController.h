#pragma once
#include "../Engine/IGameObjectController.h"
class PlayerController :
	public IGameObjectController
{
public:
	PlayerController();
	PlayerController(GameObject* player, char* name, float _sizeX, float _sizeY);
	~PlayerController();
	PlayerController(const PlayerController& controller);
	PlayerController(PlayerController&& controller) noexcept;
	PlayerController& operator=(const PlayerController& other);
	PlayerController& operator=(PlayerController&& other) noexcept;
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


#pragma once
#include "../../Engine/Objects/IGameObjectController.h"
class PlayerController :
	public IGameObjectController
{
public:
	PlayerController();
	PlayerController(GameObject* i_player, char* i_name, float i_sizeX, float i_sizeY);
	~PlayerController();
	PlayerController(const PlayerController& i_controller);
	PlayerController(PlayerController&& i_controller) noexcept;
	PlayerController& operator=(const PlayerController& i_other);
	PlayerController& operator=(PlayerController&& i_other) noexcept;
	void Setup(char* const i_playerName, const float i_playX, const float i_playY);
	void SetGameObject(GameObject* const i_object) override;
	void UpdateGameObject() override;
	Point2D getPlayerPosition() const;
private:
	char getMovement();
	void boundCheck();
	GameObject* player;
	char* name;
	float maxX;
	float maxY;
};


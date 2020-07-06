#pragma once
#include "../../Engine/Objects/IGameObjectController.h"
class MonsterController :
	public IGameObjectController
{
public:
	MonsterController();
	MonsterController(bool i_active, float i_x, float i_y, GameObject* i_monster, GameObject* i_player, char* i_name);
	~MonsterController();
	MonsterController(const MonsterController& i_controller);
	MonsterController(MonsterController&& i_controller) noexcept;
	MonsterController& operator=(const MonsterController& i_other);
	MonsterController& operator=(MonsterController&& i_other) noexcept;
	void Setup(const bool i_active, const float i_x, const float i_y, GameObject* const i_monster, GameObject* const i_player, char* const i_name);
	void SetGameObject(GameObject* const i_object) override;
	void GetFocus(GameObject* const i_object);
	void UpdateGameObject() override;
	bool getActive() const;
	Point2D getPosition() const;
private:
	void checkAndSetTime();
	unsigned int deathTime;
	const unsigned int maxTime = 4;
	float maxX;
	float maxY;
	GameObject* monster;
	GameObject* player;
	char* name;
	bool isActive;
};


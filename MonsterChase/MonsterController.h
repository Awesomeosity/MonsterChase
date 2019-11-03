#pragma once
#include "..\Engine\IGameObjectController.h"
class MonsterController :
	public IGameObjectController
{
public:
	MonsterController(bool active, float x, float y, GameObject* monster, GameObject* player);
	void Setup(GameObject* _monster, GameObject* _player);
	void SetGameObject(GameObject* object) override;
	void GetFocus(GameObject* object);
	void UpdateGameObject() override;
private:
	void checkAndSetTime();
	unsigned int deathTime;
	const unsigned int maxTime = 4;
	float maxX;
	float maxY;
	GameObject* monster;
	GameObject* player;
	bool isActive;
};


#pragma once
#include "..\Engine\IGameObjectController.h"
class RandomController :
	public IGameObjectController
{
public:
	RandomController(float x, float y, GameObject* _monster, char* _name, bool active);
	~RandomController();
	void SetGameObject(GameObject* object) override;
	void UpdateGameObject() override;
private:
	void checkAndSetTime();
	unsigned int deathTime;
	const unsigned int maxTime = 4;
	float maxX;
	float maxY;
	GameObject* monster;
	char* name;
	bool isActive;
};


#pragma once
#include "..\Engine\IGameObjectController.h"
class MonsterController :
	public IGameObjectController
{
public:
	MonsterController(bool active = false, float x = 0, float y = 0, GameObject* monster = nullptr, GameObject* player = nullptr, char* _name = nullptr);
	~MonsterController();
	MonsterController(const MonsterController& controller);
	MonsterController& operator=(const MonsterController& other);
	void Setup(bool active, float x, float y, GameObject* monster, GameObject* player, char* name);
	void SetGameObject(GameObject* object) override;
	void GetFocus(GameObject* object);
	void UpdateGameObject() override;
	bool getActive() const;
	Point2D* getPosition() const;
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


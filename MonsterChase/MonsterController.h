#pragma once
#include "../Engine/IGameObjectController.h"
class MonsterController :
	public IGameObjectController
{
public:
	MonsterController();
	MonsterController(bool active, float x, float y, GameObject* monster, GameObject* player, char* _name);
	~MonsterController();
	MonsterController(const MonsterController& controller);
	MonsterController(MonsterController&& controller) noexcept;
	MonsterController& operator=(const MonsterController& other);
	MonsterController& operator=(MonsterController&& other) noexcept;
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


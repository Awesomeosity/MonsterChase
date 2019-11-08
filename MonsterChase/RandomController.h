#pragma once
#include "..\Engine\IGameObjectController.h"
class RandomController :
	public IGameObjectController
{
public:
	RandomController(bool active, float x, float y, GameObject* _monster, char* _name);
	~RandomController();
	RandomController(const RandomController& controller);
	RandomController& operator=(const RandomController& other);
	void SetGameObject(GameObject* object) override;
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
	char* name;
	bool isActive;
};


#pragma once
#include "../../Engine/Objects/IGameObjectController.h"
class RandomController :
	public IGameObjectController
{
public:
	RandomController();
	RandomController(bool i_active, float i_x, float i_y, GameObject* i_monster, char* i_name);
	~RandomController();
	RandomController(const RandomController& i_controller);
	RandomController(RandomController&& i_controller) noexcept;
	RandomController& operator=(const RandomController& i_other);
	RandomController& operator=(RandomController&& i_other) noexcept;
	void SetGameObject(GameObject* const i_object) override;
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


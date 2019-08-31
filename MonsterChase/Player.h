#pragma once
#include <string>
#include "../Engine/GameObject.h"
#include "../Engine/Point2D.h"
class Player : public GameObject
{
public:
	Player(Point2D point, char name[]);
	~Player();
};


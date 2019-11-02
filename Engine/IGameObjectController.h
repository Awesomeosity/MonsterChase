#pragma once
#include "GameObject.h"
class IGameObjectController
{
public: 
	virtual ~IGameObjectController() = 0;
	virtual void Move() = 0;
};


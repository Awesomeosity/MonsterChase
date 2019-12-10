#pragma once
#include "GameObject.h"
class IGameObjectController
{
public:
	virtual ~IGameObjectController() {};
	virtual void SetGameObject(GameObject* i_object) = 0;
	virtual void UpdateGameObject() {};
};


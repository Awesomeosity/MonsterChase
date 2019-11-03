#pragma once
#include "GameObject.h"
class IGameObjectController
{
public: 
	virtual void SetGameObject(GameObject* object) = 0;
	virtual void UpdateGameObject() {}
};


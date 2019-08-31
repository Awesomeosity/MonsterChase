#pragma once
#include "Point2D.h"
class GameObject
{
private:
	Point2D _point;
	char* _name;
public:
	GameObject();
	GameObject(Point2D point, char *name);
	GameObject(const GameObject& gameObject);
	GameObject& operator=(const GameObject& gameObject);
	~GameObject();
	char* GetName() const;
	void SetName(char *name);
	Point2D GetPoint() const;
};


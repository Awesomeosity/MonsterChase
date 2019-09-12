#pragma once
#include "Point2D.h"
class GameObject
{
public:
	GameObject();
	GameObject(Point2D point, char* name);
	GameObject(GameObject& gameObject);
	GameObject& operator=(GameObject& gameObject);
	~GameObject();
	char* GetName();
	void SetName(char* name);
	Point2D* GetPoint();
	void SetPoint(Point2D point);
private:
	Point2D _point;
	char* _name;
};


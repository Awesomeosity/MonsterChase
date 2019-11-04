#pragma once
#include "Point2D.h"
class GameObject
{
public:
	GameObject();
	GameObject(Point2D* point);
	GameObject(GameObject& gameObject);
	GameObject& operator=(GameObject& gameObject);
	~GameObject();
	Point2D* GetPoint();
	void SetPoint(Point2D point);
private:
	Point2D _point;
};


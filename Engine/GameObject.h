#pragma once
#include "Point2D.h"
class GameObject
{
public:
	GameObject();
	GameObject(Point2D& i_point);
	GameObject(GameObject& i_gameObject);
	GameObject(GameObject&& i_gameObject) noexcept;
	GameObject& operator=(GameObject& i_gameObject);
	GameObject& operator=(GameObject&& i_gameObject) noexcept;
	~GameObject();
	Point2D* GetPoint();
	void SetPoint(Point2D i_point);
private:
	Point2D _point;
};


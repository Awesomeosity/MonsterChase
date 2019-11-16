#pragma once
#include "Point2D.h"
class GameObject
{
public:
	GameObject();
	GameObject(Point2D* point);
	GameObject(GameObject& gameObject);
	GameObject(GameObject&& gameObject) noexcept;
	GameObject& operator=(GameObject& gameObject);
	GameObject& operator=(GameObject&& gameObject) noexcept;
	~GameObject();
	Point2D* GetPoint();
	void SetPoint(Point2D point);
private:
	Point2D _point;
};


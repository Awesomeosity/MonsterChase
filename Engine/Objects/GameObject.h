#pragma once
#include "../Types/Point2D.h"
#include <map>
#include <string>
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
	Point2D GetPoint();
	void SetPoint(Point2D i_point);
	void AddComponent(std::string str, void* ptr);
	void* GetComponent(const std::string str) const;
private:
	Point2D _point;
	std::map<std::string, void*> _components;
};


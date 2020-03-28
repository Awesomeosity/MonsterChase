#include "GameObject.h"
#include <iostream>
#include <map>
#include <string>

GameObject::GameObject() : _point()
{
}

GameObject::GameObject(Point2D& i_point) : _point(i_point)
{
}

GameObject::GameObject(float X, float Y) : _point(X, Y)
{

}

GameObject::GameObject(GameObject& i_gameObject) : _point(i_gameObject.GetPoint())
{
}

GameObject::GameObject(GameObject&& i_gameObject) noexcept
	: _point()
{
	_point = i_gameObject._point;
}

GameObject& GameObject::operator=(GameObject& i_gameObject)
{
	if (this == &i_gameObject)
	{
		return *this;
	}

	_point = i_gameObject.GetPoint();

	return *this;
}

GameObject& GameObject::operator=(GameObject&& i_gameObject) noexcept
{
	if (this == &i_gameObject)
	{
		return *this;
	}

	_point = i_gameObject.GetPoint();
	return *this;
}

GameObject::~GameObject()
{
	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		delete it->second;
	}
	_components.clear();
}

Point2D GameObject::GetPoint()
{
	return _point;
}

void GameObject::SetPoint(Point2D i_point)
{
	_point = i_point;
}

void GameObject::AddComponent(std::string str, void* ptr)
{
	_components.insert(std::pair<std::string, void*>(str, ptr));
}

void* GameObject::GetComponent(const std::string str) const
{
	auto compRef = _components.find(str);
	if (compRef == _components.end())
	{
		return nullptr;
	}

	return compRef->second;
}

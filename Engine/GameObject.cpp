#include "pch.h"
#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	_point = Point2D();
	_name = new char[1];
	_name[0] = '\n';
}

GameObject::GameObject(Point2D point, char* name)
{
	_point = point;
	_name = new char[strlen(name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(name) + 1), name);
}

GameObject::GameObject(const GameObject& gameObject)
{
	_point = gameObject.GetPoint();
	_name = gameObject.GetName();
}

GameObject& GameObject::operator=(const GameObject& gameObject)
{
	if (this == &gameObject)
	{
		return *this;
	}

	_point = gameObject.GetPoint();
	_name = gameObject.GetName();
	return *this;
}

GameObject::~GameObject()
{
	delete _name;
}

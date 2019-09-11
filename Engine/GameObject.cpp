#include "pch.h"
#include "GameObject.h"
#include <iostream>

GameObject::GameObject() : _point()
{
	_name = new char[1];
	_name[0] = '\n';
}

GameObject::GameObject(Point2D point, char* name) : _point(point)
{
	_name = new char[strlen(name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(name) + 1), name);
}

GameObject::GameObject(GameObject& gameObject) : _point(*(gameObject.GetPoint()))
{
	char* name = gameObject.GetName();
	_name = new char[strlen(name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(name) + 1), name);
}

GameObject& GameObject::operator=(GameObject& gameObject)
{
	if (this == &gameObject)
	{
		return *this;
	}

	delete _name;

	_point = *(gameObject.GetPoint());

	char* name = gameObject.GetName();
	_name = new char[strlen(name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(name) + 1), name);
	return *this;
}

GameObject::~GameObject()
{
	delete _name;
}

char* GameObject::GetName()
{
	return _name;
}

void GameObject::SetName(char* name)
{
	delete _name;
	_name = new char[strlen(name) + 1];
	strcpy_s(_name, sizeof(char) * (strlen(name) + 1), name);
}

Point2D* GameObject::GetPoint()
{
	return &_point;
}

void GameObject::SetPoint(Point2D point)
{
	_point = point;
}

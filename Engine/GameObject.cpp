#include "pch.h"
#include "GameObject.h"
#include <iostream>

GameObject::GameObject() : _point()
{
}

GameObject::GameObject(Point2D* point) : _point(*point)
{
}

GameObject::GameObject(GameObject& gameObject) : _point(*(gameObject.GetPoint()))
{
}

GameObject::GameObject(GameObject&& gameObject) noexcept
	: _point()
{
	_point = gameObject._point;
}

GameObject& GameObject::operator=(GameObject& gameObject)
{
	if (this == &gameObject)
	{
		return *this;
	}

	_point = *(gameObject.GetPoint());

	return *this;
}

GameObject& GameObject::operator=(GameObject&& gameObject) noexcept
{
	if (this == &gameObject)
	{
		return *this;
	}

	_point = *(gameObject.GetPoint());
	return *this;
}

GameObject::~GameObject()
{
}

Point2D* GameObject::GetPoint()
{
	return &_point;
}

void GameObject::SetPoint(Point2D point)
{
	_point = point;
}

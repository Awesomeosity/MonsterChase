#include "pch.h"
#include "Point2D.h"


Point2D::Point2D(int x, int y)
{
	_X = x;
	_Y = y;
}

Point2D::Point2D(const Point2D& point)
{
	_X = point._X;
	_Y = point._Y;
}

Point2D Point2D::operator=(const Point2D point)
{
	if (this == &point)
	{
		return *this;
	}

	_X = point._X;
	_Y = point._Y;
	return *this;
}

int Point2D::GetX() const
{
	return _X;
}

int Point2D::GetY() const
{
	return _Y;
}

void Point2D::SetX(int x)
{
	_X = x;
}

void Point2D::SetY(int y)
{
	_X = y;
}

Point2D operator+(const Point2D &p1, const Point2D &p2)
{
	return Point2D(p1.GetX() + p2.GetX(), p1.GetY() + p2.GetY());
}

Point2D operator-(const Point2D& p1, const Point2D& p2)
{
	return Point2D(p1.GetX() - p2.GetX(), p1.GetY() - p2.GetY());
}

bool operator==(const Point2D& p1, const Point2D& p2)
{
	return (p1.GetX() == p2.GetX() && p1.GetY() == p2.GetY());
}


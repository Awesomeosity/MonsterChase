#include "pch.h"
#include "Point2D.h"


Point2D::Point2D(float x, float y)
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

Point2D Point2D::operator+=(const Point2D Point2D)
{
	_X += Point2D._X;
	_Y += Point2D._Y;
	return *this;
}

Point2D Point2D::operator-=(const Point2D Point2D)
{
	_X -= Point2D._X;
	_Y -= Point2D._Y;
	return *this;
}

Point2D Point2D::operator*=(const Point2D Point2D)
{
	_X *= Point2D._X;
	_Y *= Point2D._Y;
	return *this;
}

Point2D Point2D::operator/=(const Point2D Point2D)
{
	if (Point2D._X != 0 && Point2D._Y != 0)
	{
		_X /= Point2D._X;
		_Y /= Point2D._Y;
	}
	else
	{
		_X = 0;
		_Y = 0;
	}
	return *this;
}

float Point2D::GetX() const
{
	return _X;
}

float Point2D::GetY() const
{
	return _Y;
}

void Point2D::SetX(float x)
{
	_X = x;
}

void Point2D::SetY(float y)
{
	_Y = y;
}

void Point2D::Point2D_UnitTest()
{
	Point2D P1(0.0f, 0.0f);
	Point2D P2(0.0f, 0.0f);

	Point2D P3 = P1 + P2;
	P3 = P1 - P2;

	Point2D P4 = P1 * 0.5f;

	Point2D P5 = P1 / 2.0f;

	Point2D P6 = -P4;

	P6 *= 2.0f;
	P5 /= 4.0f;

	P2 += P1;
	P3 -= P1;

	Point2D P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;

	bool bArentEqual = P6 != P4;
}

Point2D operator+(const Point2D &p1, const Point2D &p2)
{
	return Point2D(p1.GetX() + p2.GetX(), p1.GetY() + p2.GetY());
}

Point2D operator-(const Point2D &point)
{
	return Point2D(-1 * point.GetX(), -1 * point.GetY());
}

Point2D operator-(const Point2D& p1, const Point2D& p2)
{
	return Point2D(p1.GetX() - p2.GetX(), p1.GetY() - p2.GetY());
}

Point2D operator*(const Point2D& p1, const Point2D& p2)
{
	return Point2D(p1.GetX() * p2.GetX(), p1.GetY() * p2.GetY());
}

Point2D operator/(const Point2D& p1, const Point2D& p2)
{
	if (p2.GetX() != 0 && p2.GetY() != 0)
	{
		return Point2D(p1.GetX() / p2.GetX(), p1.GetY() / p2.GetY());
	}
	else
	{
		return Point2D(0, 0);
	}
}

bool operator==(const Point2D& p1, const Point2D& p2)
{
	return (p1.GetX() == p2.GetX() && p1.GetY() == p2.GetY());
}

bool operator!=(const Point2D& p1, const Point2D& p2)
{
	return (p1.GetX() != p2.GetX() || p1.GetY() != p2.GetY());
}


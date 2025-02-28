#pragma once
#include "Point2D.h"
inline Point2D Point2D::operator=(const Point2D& i_point)
{
	if (*this == i_point)
	{
		return *this;
	}

	_X = i_point._X;
	_Y = i_point._Y;
	return *this;
}

inline Point2D Point2D::operator+=(const Point2D& i_Point2D)
{
	_X += i_Point2D._X;
	_Y += i_Point2D._Y;
	return *this;
}

inline Point2D Point2D::operator-=(const Point2D& i_Point2D)
{
	_X -= i_Point2D._X;
	_Y -= i_Point2D._Y;
	return *this;
}

inline Point2D Point2D::operator*=(const float i_scalar)
{
	_X *= i_scalar;
	_Y *= i_scalar;
	return *this;
}

inline Point2D Point2D::operator/=(const float i_scalar)
{
	if (i_scalar != 0)
	{
		_X /= i_scalar;
		_Y /= i_scalar;
	}
	else
	{
		_X = 0;
		_Y = 0;
	}
	return *this;
}

inline float Point2D::GetX() const
{
	return _X;
}

inline float Point2D::GetY() const
{
	return _Y;
}

inline Point2D operator+(const Point2D& i_p1, const Point2D& i_p2)
{
	return Point2D(i_p1.GetX() + i_p2.GetX(), i_p1.GetY() + i_p2.GetY());
}

inline Point2D operator-(const Point2D& i_point)
{
	return Point2D(-1 * i_point.GetX(), -1 * i_point.GetY());
}

inline Point2D operator-(const Point2D& i_p1, const Point2D& i_p2)
{
	return Point2D(i_p1.GetX() - i_p2.GetX(), i_p1.GetY() - i_p2.GetY());
}

inline Point2D operator*(const Point2D& i_p1, const float i_scalar)
{
	return Point2D(i_p1.GetX() * i_scalar, i_p1.GetY() * i_scalar);
}

inline Point2D operator*(const float i_scalar, const Point2D& i_p1)
{
	return Point2D(i_p1.GetX() * i_scalar, i_p1.GetY() * i_scalar);
}

inline Point2D operator*(const Point2D& i_p1, const Point2D& i_p2)
{
	return Point2D(i_p1.GetX() * i_p2.GetX(), i_p1.GetY() * i_p2.GetY());
}

inline Point2D operator/(const Point2D& i_p1, const float i_scalar)
{
	if (i_scalar != 0.0f)
	{
		return Point2D(i_p1.GetX() / i_scalar, i_p1.GetY() / i_scalar);
	}
	else
	{
		return Point2D(0, 0);
	}
}

inline bool operator==(const Point2D& i_p1, const Point2D& i_p2)
{
	return (i_p1.GetX() == i_p2.GetX() && i_p1.GetY() == i_p2.GetY());
}

inline bool operator!=(const Point2D& i_p1, const Point2D& i_p2)
{
	return !(i_p1.GetX() == i_p2.GetX() && i_p1.GetY() == i_p2.GetY());
}

inline void Point2D::Point2D_UnitTest()
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

#pragma warning (disable: 4189)
	bool bArentEqual = P6 != P4;
#pragma warning (disable: 4189)

}
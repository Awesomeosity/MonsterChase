#pragma once
inline Point2D Point2D::operator=(const Point2D point)
{
	if (this == &point)
	{
		return *this;
	}

	_X = point._X;
	_Y = point._Y;
	return *this;
}

inline Point2D Point2D::operator+=(const Point2D Point2D)
{
	_X += Point2D._X;
	_Y += Point2D._Y;
	return *this;
}

inline Point2D Point2D::operator-=(const Point2D Point2D)
{
	_X -= Point2D._X;
	_Y -= Point2D._Y;
	return *this;
}

inline Point2D Point2D::operator*=(float scalar)
{
	_X *= scalar;
	_Y *= scalar;
	return *this;
}

inline Point2D Point2D::operator/=(float scalar)
{
	if (scalar != 0)
	{
		_X /= scalar;
		_Y /= scalar;
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

inline Point2D operator+(const Point2D& p1, const Point2D& p2)
{
	return Point2D(p1.GetX() + p2.GetX(), p1.GetY() + p2.GetY());
}

inline Point2D operator-(const Point2D& point)
{
	return Point2D(-1 * point.GetX(), -1 * point.GetY());
}

inline Point2D operator-(const Point2D& p1, const Point2D& p2)
{
	return Point2D(p1.GetX() - p2.GetX(), p1.GetY() - p2.GetY());
}

inline Point2D operator*(const Point2D& p1, float scalar)
{
	return Point2D(p1.GetX() * scalar, p1.GetY() * scalar);
}

inline Point2D operator/(const Point2D& p1, float scalar)
{
	if (scalar != 0.0f)
	{
		return Point2D(p1.GetX() / scalar, p1.GetY() / scalar);
	}
	else
	{
		return Point2D(0, 0);
	}
}

inline bool operator==(const Point2D& p1, const Point2D& p2)
{
	return (p1.GetX() == p2.GetX() && p1.GetY() == p2.GetY());
}

inline bool operator!=(const Point2D& p1, const Point2D& p2)
{
	return !(p1.GetX() == p2.GetX() && p1.GetY() == p2.GetY());
}


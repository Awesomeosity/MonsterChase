#pragma once
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


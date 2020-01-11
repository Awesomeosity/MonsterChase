#include "Point2D.h"


Point2D::Point2D()
	:_X(0), _Y(0)
{
}

Point2D::Point2D(const float i_x, const float i_y)
	: _X(i_x), _Y(i_y)
{
}

Point2D::Point2D(const Point2D& i_point)
	: _X(i_point._X), _Y(i_point._Y)
{
}

Point2D::Point2D(Point2D&& i_point) noexcept
	: _X(0), _Y(0)
{
	_X = i_point._X;
	_Y = i_point._Y;

	i_point._X = 0;
	i_point._Y = 0;
}

Point2D& Point2D::operator=(Point2D&& i_point) noexcept
{
	if (this != &i_point)
	{
		_X = i_point._X;
		_Y = i_point._Y;

		i_point._X = 0;
		i_point._Y = 0;
	}

	return *this;
}

void Point2D::SetX(const float i_x)
{
	_X = i_x;
}

void Point2D::SetY(const float i_y)
{
	_Y = i_y;
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

#pragma warning (disable: 4189)
	bool bArentEqual = P6 != P4;
#pragma warning (disable: 4189)

}
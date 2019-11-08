#include "pch.h"
#include "Point2D.h"


Point2D::Point2D(const float x, const float y)
{
	_X = x;
	_Y = y;
}

Point2D::Point2D(const Point2D& point)
{
	_X = point._X;
	_Y = point._Y;
}

void Point2D::SetX(const float x)
{
	_X = x;
}

void Point2D::SetY(const float y)
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

#pragma warning (disable: 4189)
	bool bArentEqual = P6 != P4;
#pragma warning (disable: 4189)

}
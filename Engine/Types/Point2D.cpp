#include "Point2D.h"
#include "../Physics/FloatCalcs.h"
#include <assert.h>

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
	assert(!FloatCalcs::isNaN(_X));
	_Y = i_point._Y;
	assert(!FloatCalcs::isNaN(_Y));

	i_point._X = 0;
	i_point._Y = 0;
}

Point2D& Point2D::operator=(Point2D&& i_point) noexcept
{
	if (this != &i_point)
	{
		_X = i_point._X;
		assert(!FloatCalcs::isNaN(_X));
		_Y = i_point._Y;
		assert(!FloatCalcs::isNaN(_Y));

		i_point._X = 0;
		i_point._Y = 0;
	}

	return *this;
}

void Point2D::SetX(const float i_x)
{
	assert(!FloatCalcs::isNaN(i_x));
	_X = i_x;
}

void Point2D::SetY(const float i_y)
{
	assert(!FloatCalcs::isNaN(i_y));
	_Y = i_y;
}


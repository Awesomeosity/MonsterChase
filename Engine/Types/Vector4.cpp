#include "Vector4.h"
#include "../Physics/FloatCalcs.h"
#include <assert.h>

Vector4::Vector4():
	_X(0.0f), _Y(0.0f), _Z(0.0f), _W(0.0f)
{

}

Vector4::Vector4(float X, float Y, float Z, float W)
	: _X(X), _Y(Y), _Z(Z), _W(W)
{
}

Vector4::Vector4(float X, float Y, float Z)
	: _X(X), _Y(Y), _Z(Z), _W(1.0f)
{
}

Vector4::Vector4(float X, float Y)
	: _X(X), _Y(Y), _Z(1.0f), _W(0.0f)
{
}

Vector4::Vector4(const Vector4& i_vector)
	: _X(i_vector._X), _Y(i_vector._Y), _Z(i_vector._Z), _W(i_vector._W)
{
}

Vector4::Vector4(const Point2D& i_point)
	: _X(i_point.GetX()), _Y(i_point.GetY()), _Z(0.0f), _W(1.0f)
{
}

Vector4::Vector4(Vector4&& i_vector) noexcept
	: _X(0.0f), _Y(0.0f), _Z(0.0f), _W(0.0f)
{
	assert(!FloatCalcs::isNaN(i_vector._X));
	assert(!FloatCalcs::isNaN(i_vector._Y));
	assert(!FloatCalcs::isNaN(i_vector._Z));
	assert(!FloatCalcs::isNaN(i_vector._W));

	_X = i_vector._X;
	_Y = i_vector._Y;
	_Z = i_vector._Z;
	_W = i_vector._W;

	i_vector._X	= 0;
	i_vector._Y	= 0;
	i_vector._Z	= 0;
	i_vector._W	= 0;
}

Vector4::Vector4(Point2D&& i_point) noexcept
	: _X(0.0f), _Y(0.0f), _Z(0.0f), _W(1.0f)
{
	assert(!FloatCalcs::isNaN(i_point.GetX()));
	assert(!FloatCalcs::isNaN(i_point.GetY()));

	_X = i_point.GetX();
	_Y = i_point.GetY();

	i_point.SetX(0);
	i_point.SetY(0);
}

Vector4& Vector4::operator=(Vector4&& i_vector) noexcept
{
	if (this != &i_vector)
	{
		assert(!FloatCalcs::isNaN(i_vector._X));
		assert(!FloatCalcs::isNaN(i_vector._Y));
		assert(!FloatCalcs::isNaN(i_vector._Z));
		assert(!FloatCalcs::isNaN(i_vector._W));

		_X = i_vector._X;
		_Y = i_vector._Y;
		_Z = i_vector._Z;
		_W = i_vector._W;

		i_vector._X	= 0;
		i_vector._Y	= 0;
		i_vector._Z	= 0;
		i_vector._W	= 0;
	}

	return *this;
}

Vector4& Vector4::operator=(Point2D&& i_point) noexcept
{
	assert(!FloatCalcs::isNaN(i_point.GetX()));
	assert(!FloatCalcs::isNaN(i_point.GetY()));
	
	_X = i_point.GetX();
	_Y = i_point.GetY();
	_Z = 0.0f;
	_W = 1.0f;
	return *this;
}

void Vector4::SetX(const float value)
{
	assert(!FloatCalcs::isNaN(value));
	_X = value;
}

void Vector4::SetY(const float value)
{
	assert(!FloatCalcs::isNaN(value));
	_Y = value;
}

void Vector4::SetZ(const float value)
{
	assert(!FloatCalcs::isNaN(value));
	_Z = value;
}

void Vector4::SetW(const float value)
{
	assert(!FloatCalcs::isNaN(value));
	_W = value;
}
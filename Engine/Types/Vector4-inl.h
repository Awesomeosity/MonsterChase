#pragma once
#include "Vector4.h"
#include "../Physics/FloatCalcs.h"

#include <assert.h>

inline Vector4 Vector4::operator+=(const Vector4& i_vector)
{
	assert(!FloatCalcs::isNaN(i_vector._X));
	assert(!FloatCalcs::isNaN(i_vector._Y));
	assert(!FloatCalcs::isNaN(i_vector._Z));
	assert(!FloatCalcs::isNaN(i_vector._W));

	_X += i_vector._X;
	_Y += i_vector._Y;
	_Z += i_vector._Z;
	_W += i_vector._W;
	return *this;
}

inline Vector4 Vector4::operator+=(const Point2D& i_point)
{
	assert(!FloatCalcs::isNaN(i_point.GetX()));
	assert(!FloatCalcs::isNaN(i_point.GetY()));

	_X += i_point.GetX();
	_Y += i_point.GetY();
	return *this;
}

inline Vector4 Vector4::operator-=(const Vector4& i_vector)
{
	assert(!FloatCalcs::isNaN(i_vector._X));
	assert(!FloatCalcs::isNaN(i_vector._Y));
	assert(!FloatCalcs::isNaN(i_vector._Z));
	assert(!FloatCalcs::isNaN(i_vector._W));

	_X -= i_vector._X;
	_Y -= i_vector._Y;
	_Z -= i_vector._Z;
	_W -= i_vector._W;
	return *this;
}

inline Vector4 Vector4::operator-=(const Point2D& i_point)
{
	assert(!FloatCalcs::isNaN(i_point.GetX()));
	assert(!FloatCalcs::isNaN(i_point.GetY()));

	_X -= i_point.GetX();
	_Y -= i_point.GetY();
	return *this;
}

inline Vector4 Vector4::operator*=(const float i_scalar)
{
	assert(!FloatCalcs::isNaN(i_scalar));
	_X *= i_scalar;
	_Y *= i_scalar;
	_Z *= i_scalar;
	_W *= i_scalar;
	return *this;
}

inline Vector4 Vector4::operator/=(const float i_scalar)
{
	assert(!FloatCalcs::isZero(i_scalar));
	assert(!FloatCalcs::isNaN(i_scalar));
	_X /= i_scalar;
	_Y /= i_scalar;
	_Z /= i_scalar;
	_W /= i_scalar;
	return *this;
}

inline float Vector4::GetX() const
{
	return _X;
}

inline float Vector4::GetY() const
{
	return _Y;
}

inline float Vector4::GetZ() const
{
	return _Z;
}

inline float Vector4::GetW() const
{
	return _W;
}

inline Vector4 operator+(const Vector4& i_v1, const Vector4& i_v2)
{
	return Vector4(i_v1.GetX() + i_v2.GetX(),
		i_v1.GetY() + i_v2.GetY(),
		i_v1.GetZ() + i_v2.GetZ(),
		i_v1.GetW() + i_v2.GetW());
}

inline Vector4 operator-(const Vector4& i_v1)
{
	return Vector4(-1 * i_v1.GetX(),
		-1 * i_v1.GetY(),
		-1 * i_v1.GetZ(),
		-1 * i_v1.GetW());
}

inline Vector4 operator-(const Vector4& i_v1, const Vector4& i_v2)
{
	return Vector4(i_v1.GetX() - i_v2.GetX(),
		i_v1.GetY() - i_v2.GetY(),
		i_v1.GetZ() - i_v2.GetZ(),
		i_v1.GetW() - i_v2.GetW());
}

inline Vector4 operator*(const Vector4& i_v1, const float i_scalar)
{
	assert(!FloatCalcs::isNaN(i_scalar));
	return Vector4(i_scalar * i_v1.GetX(),
		i_scalar * i_v1.GetY(),
		i_scalar * i_v1.GetZ(),
		i_scalar * i_v1.GetW());
}

inline Vector4 operator*(const float i_scalar, const Vector4& i_v1)
{
	assert(!FloatCalcs::isNaN(i_scalar));
	return Vector4(i_scalar * i_v1.GetX(),
		i_scalar * i_v1.GetY(),
		i_scalar * i_v1.GetZ(),
		i_scalar * i_v1.GetW());
}

inline Vector4 operator*(const Vector4& i_v1, const Vector4& i_v2)
{
	return Vector4(i_v2.GetX() * i_v1.GetX(),
		i_v2.GetY() * i_v1.GetY(),
		i_v2.GetZ() * i_v1.GetZ(),
		i_v2.GetW() * i_v1.GetW());
}

inline Vector4 operator/(const Vector4& i_v1, const float i_scalar)
{
	assert(!FloatCalcs::isNaN(i_scalar));
	assert(!FloatCalcs::isZero(i_scalar));
	return Vector4(i_v1.GetX() / i_scalar,
		i_v1.GetY() / i_scalar,
		i_v1.GetZ() / i_scalar,
		i_v1.GetW() / i_scalar);
}

inline bool operator==(const Vector4& i_v1, const Vector4& i_v2)
{
	if (FloatCalcs::relativeEquality(i_v1.GetX(), i_v2.GetX()) &&
		FloatCalcs::relativeEquality(i_v1.GetY(), i_v2.GetY()) &&
		FloatCalcs::relativeEquality(i_v1.GetZ(), i_v2.GetZ()) &&
		FloatCalcs::relativeEquality(i_v1.GetW(), i_v2.GetW()))
	{
		return true;
	}
	return false;
}

inline bool operator!=(const Vector4& i_v1, const Vector4& i_v2)
{
	if (FloatCalcs::relativeEquality(i_v1.GetX(), i_v2.GetX()) &&
		FloatCalcs::relativeEquality(i_v1.GetY(), i_v2.GetY()) &&
		FloatCalcs::relativeEquality(i_v1.GetZ(), i_v2.GetZ()) &&
		FloatCalcs::relativeEquality(i_v1.GetW(), i_v2.GetW()))
	{
		return false;
	}
	return true;

}
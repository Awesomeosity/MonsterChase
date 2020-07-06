#pragma once
#include "Matrix4.h"
#include <cassert>
#include "../Physics/FloatCalcs.h"
#include "Vector4.h"

//bruh
const float PI = 3.14159265358979323846f;

Matrix4::Matrix4()
	: values()
{
}

Matrix4::Matrix4(float x11, float x12, float x13, float x14, float x21, float x22, float x23, float x24, float x31, float x32, float x33, float x34, float x41, float x42, float x43, float x44)
	: values{x11, x12, x13, x14,
			 x21, x22, x23, x24,
			 x31, x32, x33, x34,
			 x41, x42, x43, x44}
{
}

Matrix4::Matrix4(const Matrix4& i_matrix)
	: values(i_matrix.values)
{
}

//Constructs from a series of column vectors
Matrix4::Matrix4(const Vector4& xx0, const Vector4& xx1, const Vector4& xx2, const Vector4& xx3)
	: values{ xx0.GetX(), xx1.GetX(), xx2.GetX(), xx3.GetX(),
			  xx0.GetY(), xx1.GetY(), xx2.GetY(), xx3.GetY(),
			  xx0.GetZ(), xx1.GetZ(), xx2.GetZ(), xx3.GetZ(),
			  xx0.GetW(), xx1.GetW(), xx2.GetW(), xx3.GetW()}
{
}

Matrix4::Matrix4(Matrix4&& i_matrix) noexcept
	: values{0.0f}
{
	for (size_t i = 0; i < 16; i++)
	{
#if _DEBUG
		assert(!FloatCalcs::isNaN(i_matrix.values[i]));
#endif
		values[i] = i_matrix.values[i];
		i_matrix.values[i] = 0;
	}
}

Matrix4& Matrix4::operator=(Matrix4&& i_matrix) noexcept
{
	if (&i_matrix == this)
	{
		return *this;
	}

	for (size_t i = 0; i < 16; i++)
	{
#if _DEBUG
		assert(!FloatCalcs::isNaN(i_matrix.values[i]));
#endif
		values[i] = i_matrix.values[i];
		i_matrix.values[i] = 0;
	}

	return *this;
}

//Rotates counterclockwise, angle given is in degrees?
Matrix4 Matrix4::GenerateRotationMatrix(const float angle)
{
	float radians = angle * PI / 180.0f;
	return Matrix4(cos(radians), -sin(radians), 0.0f, 0.0f,
					sin(radians), cos(radians), 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::GenerateScalingMatrix(const float scale_X, const float scale_Y)
{
	return Matrix4(scale_X, 0.0f, 0.0f, 1.0f,
					0.0f, scale_Y, 0, 1.0f,
					0.0f, 0.0f, 1.0f, 1.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::GenerateTransformMatrix(const float dX, const float dY, const float dZ)
{
	return Matrix4(1.0f, 0.0f, 0.0f, dX,
					0.0f, 1.0f, 0.0f, dY,
					0.0f, 0.0f, 1.0f, dZ,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::GenerateHomogenous(const float dX, const float dY, const float angle)
{
	float radians = angle * PI / 180.0f;
	return Matrix4(cos(radians), -sin(radians), 0.0f, dX,
		sin(radians), cos(radians), 0.0f, dY,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

}

void Matrix4::Transpose()
{
	swap(1, 4);
	swap(2, 8);
	swap(3, 12);
	swap(6, 9);
	swap(7, 13);
	swap(11, 14);
}

Matrix4 Matrix4::GenerateTranspose() const
{
	return Matrix4(values[0], values[4], values[8], values[12],
					values[1], values[5], values[9], values[13],
					values[2], values[6], values[10], values[14],
					values[3], values[7], values[11], values[15]);
}

//Generates an inverse matrix using the shortcut for transformation matrices
void Matrix4::Invert()
{
	assert(FloatCalcs::isZero(values[12]));
	assert(FloatCalcs::isZero(values[13]));
	assert(FloatCalcs::isZero(values[14]));
	assert(FloatCalcs::relativeEquality(values[15], 1.0f));
	if (FloatCalcs::isZero(values[12]) && FloatCalcs::isZero(values[13]) && FloatCalcs::isZero(values[14]) && FloatCalcs::relativeEquality(values[15], 1.0f))
	{
		float tx_1 = -values[0] * values[3] - values[1] * values[7] - values[2] * values[11];
		float tx_2 = -values[4] * values[3] - values[5] * values[7] - values[6] * values[11];
		float tx_3 = -values[8] * values[3] - values[9] * values[7] - values[10] * values[11];

		swap(1, 4);
		swap(2, 8);
		swap(6, 9);

		values[3] = tx_1;
		values[7] = tx_2;
		values[11] = tx_3;
	}
}

Matrix4 Matrix4::GenerateInvert() const
{
	assert(FloatCalcs::isZero(values[12]));
	assert(FloatCalcs::isZero(values[13]));
	assert(FloatCalcs::isZero(values[14]));
	assert(FloatCalcs::relativeEquality(values[15], 1.0f));

	float tx_1 = 0.0f;
	float tx_2 = 0.0f;
	float tx_3 = 0.0f;

	if (FloatCalcs::isZero(values[12]) && FloatCalcs::isZero(values[13]) && FloatCalcs::isZero(values[14]) && FloatCalcs::relativeEquality(values[15], 1.0f))
	{
		tx_1 = -values[0] * values[3] - values[1] * values[7] - values[2] * values[11];
		tx_2 = -values[4] * values[3] - values[5] * values[7] - values[6] * values[11];
		tx_3 = -values[8] * values[3] - values[9] * values[7] - values[10] * values[11];
	}

	return Matrix4(values[0], values[4], values[8], tx_1, 
					values[1], values[5], values[9], tx_2,
					values[2], values[6], values[10], tx_3,
					0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix4::swap(int index_1, int index_2)
{
	float temp = values[index_1];
	values[index_1] = values[index_2];
	values[index_2] = temp;
}
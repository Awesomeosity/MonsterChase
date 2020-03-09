#include "Matrix4.h"
#include <cassert>
#include "../Physics/FloatCalcs.h"

Matrix4::Matrix4()
	: values()
{
}

Matrix4::Matrix4(float x11, float x12, float x13, float x14, float x21, float x22, float x23, float x24, float x31, float x32, float x33, float x34, float x41, float x42, float x43, float x44)
	: values{x11, x12, x13, x14, x21, x22, x23, x24, x31, x32, x33, x34, x41, x42, x43, x44}
{
}

Matrix4::Matrix4(const Matrix4& i_matrix)
	: values(i_matrix.values)
{
}

Matrix4::Matrix4(const Vector4& xx1, const Vector4& xx2, const Vector4& xx3, const Vector4& xx4)
	: values{ xx1.GetX(), xx1.GetY(), xx1.GetZ(), xx1.GetW(), xx2.GetX(), xx2.GetY(), xx2.GetZ(), xx2.GetW(), xx3.GetX(), xx3.GetY(), xx3.GetZ(), xx3.GetW(), xx4.GetX(), xx4.GetY(), xx4.GetZ(), xx4.GetW() }
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

Matrix4 Matrix4::GenerateRotationMatrix(const float angle)
{
	return Matrix4(cos(angle), -sin(angle), 0.0f, 0.0f,
					sin(angle), cos(angle), 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::GenerateScalingMatrix(const float scale_X, const float scale_Y)
{
	return Matrix4(scale_X, 0.0f, 0.0f, 0.0f,
					0.0f, scale_Y, 0, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 Matrix4::GenerateTransformMatrix(const float dX, const float dY, const float dZ)
{
	return Matrix4(1.0f, 0.0f, 0.0f, dX,
					0.0f, 1.0f, 0.0f, dY,
					0.0f, 0.0f, 1.0f, dZ,
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

Matrix4 Matrix4::GenerateTranspose()
{
	return Matrix4(values[0], values[4], values[8], values[12],
					values[1], values[5], values[9], values[13],
					values[2], values[6], values[10], values[14],
					values[3], values[7], values[11], values[15]);
}

void Matrix4::Invert()
{
	if (FloatCalcs::isZero(values[12]) && FloatCalcs::isZero(values[13]) && FloatCalcs::isZero(values[14]) && FloatCalcs::relativeEquality(values[15], 1.0f))
	{

	}
}

Matrix4 Matrix4::GenerateInvert()
{
	return Matrix4();
}

void Matrix4::swap(int index_1, int index_2)
{
	float temp = values[index_1];
	values[index_1] = values[index_2];
	values[index_2] = temp;
}
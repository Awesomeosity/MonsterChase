#pragma once
#include "Matrix4.h"
#include <assert.h>
#include "../Physics/FloatCalcs.h"
#include "Vector4.h"
inline Matrix4 Matrix4::operator=(const Matrix4& i_matrix)
{
	if (*this == i_matrix)
	{
		return *this;
	}

	values[0] = i_matrix.values[0];
	values[1] = i_matrix.values[1];
	values[2] = i_matrix.values[2];
	values[3] = i_matrix.values[3];

	values[4] = i_matrix.values[4];
	values[5] = i_matrix.values[5];
	values[6] = i_matrix.values[6];
	values[7] = i_matrix.values[7];

	values[8] = i_matrix.values[8];
	values[9] = i_matrix.values[9];
	values[10] = i_matrix.values[10];
	values[11] = i_matrix.values[11];

	values[12] = i_matrix.values[12];
	values[13] = i_matrix.values[13];
	values[14] = i_matrix.values[14];
	values[15] = i_matrix.values[15];

	return *this;
}

inline Matrix4 Matrix4::operator+=(const Matrix4& i_matrix)
{
	values[0] += i_matrix.values[0];
	values[1] += i_matrix.values[1];
	values[2] += i_matrix.values[2];
	values[3] += i_matrix.values[3];

	values[4] += i_matrix.values[4];
	values[5] += i_matrix.values[5];
	values[6] += i_matrix.values[6];
	values[7] += i_matrix.values[7];

	values[8] += i_matrix.values[8];
	values[9] += i_matrix.values[9];
	values[10] += i_matrix.values[10];
	values[11] += i_matrix.values[11];

	values[12] += i_matrix.values[12];
	values[13] += i_matrix.values[13];
	values[14] += i_matrix.values[14];
	values[15] += i_matrix.values[15];
	return *this;
}

inline Matrix4 Matrix4::operator-=(const Matrix4& i_matrix)
{
	values[0] -= i_matrix.values[0];
	values[1] -= i_matrix.values[1];
	values[2] -= i_matrix.values[2];
	values[3] -= i_matrix.values[3];
			  
	values[4] -= i_matrix.values[4];
	values[5] -= i_matrix.values[5];
	values[6] -= i_matrix.values[6];
	values[7] -= i_matrix.values[7];
			  
	values[8] -= i_matrix.values[8];
	values[9] -= i_matrix.values[9];
	values[10] -= i_matrix.values[10];
	values[11] -= i_matrix.values[11];
			   
	values[12] -= i_matrix.values[12];
	values[13] -= i_matrix.values[13];
	values[14] -= i_matrix.values[14];
	values[15] -= i_matrix.values[15];
	return *this;
}

inline Matrix4 Matrix4::operator*=(const float i_scalar)
{
	assert(!FloatCalcs::isNaN(i_scalar));
	values[0] *= i_scalar;
	values[1] *= i_scalar;
	values[2] *= i_scalar;
	values[3] *= i_scalar;
			  
	values[4] *= i_scalar;
	values[5] *= i_scalar;
	values[6] *= i_scalar;
	values[7] *= i_scalar;

	values[8] *= i_scalar;
	values[9] *= i_scalar;
	values[10] *= i_scalar;
	values[11] *= i_scalar;
			   
	values[12] *= i_scalar;
	values[13] *= i_scalar;
	values[14] *= i_scalar;
	values[15] *= i_scalar;
	return *this;
}

inline Matrix4 Matrix4::operator/=(const float i_scalar)
{
	assert(!FloatCalcs::isNaN(i_scalar));
	assert(!FloatCalcs::isZero(i_scalar));
	values[0] /= i_scalar;
	values[1] /= i_scalar;
	values[2] /= i_scalar;
	values[3] /= i_scalar;
			  
	values[4] /= i_scalar;
	values[5] /= i_scalar;
	values[6] /= i_scalar;
	values[7] /= i_scalar;
			  
	values[8] /= i_scalar;
	values[9] /= i_scalar;
	values[10] /= i_scalar;
	values[11] /= i_scalar;
			   
	values[12] /= i_scalar;
	values[13] /= i_scalar;
	values[14] /= i_scalar;
	values[15] /= i_scalar;
	return *this;

}

inline float& Matrix4::operator()(unsigned int x, unsigned int y)
{
	assert(y * 4 + x < 16);
	return values[y * (unsigned int)4 + x];
}

inline Vector4 Matrix4::getRow(const unsigned int rowNum) const
{
	assert(rowNum < 4);
	return Vector4(values[rowNum * 4], values[rowNum * 4 + 1], values[rowNum * 4 + 2], values[rowNum * 4 + 3]);
}

inline Vector4 Matrix4::getCol(const unsigned int colNum)
{
	assert(colNum < 4);
	return Vector4(values[colNum], values[colNum + 4], values[colNum + 8], values[colNum + 12]);
}

inline Matrix4 operator+(const Matrix4& i_m1, const Matrix4& i_m2)
{
	return Matrix4(i_m1.values[0] + i_m2.values[0], i_m1.values[1] + i_m2.values[1], i_m1.values[2] + i_m2.values[2], i_m1.values[3] + i_m2.values[3], 
				   i_m1.values[4] + i_m2.values[4], i_m1.values[5] + i_m2.values[5], i_m1.values[6] + i_m2.values[6], i_m1.values[7] + i_m2.values[7], 
				   i_m1.values[8] + i_m2.values[8], i_m1.values[9] + i_m2.values[9], i_m1.values[10] + i_m2.values[10], i_m1.values[11] + i_m2.values[11], 
				   i_m1.values[12] + i_m2.values[12], i_m1.values[13] + i_m2.values[13], i_m1.values[14] + i_m2.values[14], i_m1.values[15] + i_m2.values[15]);
}

inline Matrix4 operator-(const Matrix4& i_m1, const Matrix4& i_m2)
{
	return Matrix4(i_m1.values[0] - i_m2.values[0], i_m1.values[1] - i_m2.values[1], i_m1.values[2] - i_m2.values[2], i_m1.values[3] - i_m2.values[3],
				   i_m1.values[4] - i_m2.values[4], i_m1.values[5] - i_m2.values[5], i_m1.values[6] - i_m2.values[6], i_m1.values[7] - i_m2.values[7],
				   i_m1.values[8] - i_m2.values[8], i_m1.values[9] - i_m2.values[9], i_m1.values[10] - i_m2.values[10], i_m1.values[11] - i_m2.values[11],
				   i_m1.values[12] - i_m2.values[12], i_m1.values[13] - i_m2.values[13], i_m1.values[14] - i_m2.values[14], i_m1.values[15] - i_m2.values[15]);
}

inline Matrix4 operator*(const Matrix4& i_m, const float scalar)
{
	assert(!FloatCalcs::isNaN(scalar));
	return Matrix4(i_m.values[0] * scalar, i_m.values[1] * scalar, i_m.values[2] * scalar, i_m.values[3] * scalar,
				   i_m.values[4] * scalar, i_m.values[5] * scalar, i_m.values[6] * scalar, i_m.values[7] * scalar,
				   i_m.values[8] * scalar, i_m.values[9] * scalar, i_m.values[10] * scalar, i_m.values[11] * scalar,
				   i_m.values[12] * scalar, i_m.values[13] * scalar, i_m.values[14] * scalar, i_m.values[15] * scalar);
}

inline Matrix4 operator*(const float scalar, const Matrix4& i_m)
{
	assert(!FloatCalcs::isNaN(scalar));
	return Matrix4(i_m.values[0] * scalar, i_m.values[1] * scalar, i_m.values[2] * scalar, i_m.values[3] * scalar,
		i_m.values[4] * scalar, i_m.values[5] * scalar, i_m.values[6] * scalar, i_m.values[7] * scalar,
		i_m.values[8] * scalar, i_m.values[9] * scalar, i_m.values[10] * scalar, i_m.values[11] * scalar,
		i_m.values[12] * scalar, i_m.values[13] * scalar, i_m.values[14] * scalar, i_m.values[15] * scalar);
}

inline Matrix4 operator*(const Matrix4& i_m1, const Matrix4& i_m2)
{
	Matrix4 retMatrix = Matrix4();
	for (int i = 0; i < 16; i++)
	{
		int x = i % 4;
		int y = i / 4;

		float v_1 = i_m1.values[y * (unsigned int)4 + (unsigned int)0] * i_m2.values[x];
		float v_2 = i_m1.values[y * (unsigned int)4 + (unsigned int)1] * i_m2.values[(unsigned int)4 + x];
		float v_3 = i_m1.values[y * (unsigned int)4 + (unsigned int)2] * i_m2.values[(unsigned int)8 + x];
		float v_4 = i_m1.values[y * (unsigned int)4 + (unsigned int)3] * i_m2.values[(unsigned int)12 + x];
		retMatrix.values[i] = v_1 + v_2 + v_3 + v_4;
	}
	return retMatrix;
}

inline Matrix4 operator/(const Matrix4& i_m, const float scalar)
{
	assert(!FloatCalcs::isNaN(scalar));
	assert(!FloatCalcs::isZero(scalar));
	return Matrix4(i_m.values[0] / scalar, i_m.values[1] / scalar, i_m.values[2] / scalar, i_m.values[3] / scalar,
				   i_m.values[4] / scalar, i_m.values[5] / scalar, i_m.values[6] / scalar, i_m.values[7] / scalar,
				   i_m.values[8] / scalar, i_m.values[9] / scalar, i_m.values[10] / scalar, i_m.values[11] / scalar,
				   i_m.values[12] / scalar, i_m.values[13] / scalar, i_m.values[14] / scalar, i_m.values[15] / scalar);
}

inline bool operator==(const Matrix4& i_m1, const Matrix4& i_m2)
{
	//oh boy
	if (FloatCalcs::relativeEquality(i_m1.values[0], i_m2.values[0]) &&
		FloatCalcs::relativeEquality(i_m1.values[1], i_m2.values[1]) &&
		FloatCalcs::relativeEquality(i_m1.values[2], i_m2.values[2]) &&
		FloatCalcs::relativeEquality(i_m1.values[3], i_m2.values[3]) &&

		FloatCalcs::relativeEquality(i_m1.values[4], i_m2.values[4]) &&
		FloatCalcs::relativeEquality(i_m1.values[5], i_m2.values[5]) &&
		FloatCalcs::relativeEquality(i_m1.values[6], i_m2.values[6]) &&
		FloatCalcs::relativeEquality(i_m1.values[7], i_m2.values[7]) &&

		FloatCalcs::relativeEquality(i_m1.values[8], i_m2.values[8]) &&
		FloatCalcs::relativeEquality(i_m1.values[9], i_m2.values[9]) &&
		FloatCalcs::relativeEquality(i_m1.values[10], i_m2.values[10]) &&
		FloatCalcs::relativeEquality(i_m1.values[11], i_m2.values[11]) &&

		FloatCalcs::relativeEquality(i_m1.values[12], i_m2.values[12]) &&
		FloatCalcs::relativeEquality(i_m1.values[13], i_m2.values[13]) &&
		FloatCalcs::relativeEquality(i_m1.values[14], i_m2.values[14]) &&
		FloatCalcs::relativeEquality(i_m1.values[15], i_m2.values[15]))
	{
		return true;
	}

	return false;
}

inline bool operator!=(const Matrix4& i_m1, const Matrix4& i_m2)
{
	//oh boy
	if (FloatCalcs::relativeEquality(i_m1.values[0], i_m2.values[0]) &&
		FloatCalcs::relativeEquality(i_m1.values[1], i_m2.values[1]) &&
		FloatCalcs::relativeEquality(i_m1.values[2], i_m2.values[2]) &&
		FloatCalcs::relativeEquality(i_m1.values[3], i_m2.values[3]) &&

		FloatCalcs::relativeEquality(i_m1.values[4], i_m2.values[4]) &&
		FloatCalcs::relativeEquality(i_m1.values[5], i_m2.values[5]) &&
		FloatCalcs::relativeEquality(i_m1.values[6], i_m2.values[6]) &&
		FloatCalcs::relativeEquality(i_m1.values[7], i_m2.values[7]) &&

		FloatCalcs::relativeEquality(i_m1.values[8], i_m2.values[8]) &&
		FloatCalcs::relativeEquality(i_m1.values[9], i_m2.values[9]) &&
		FloatCalcs::relativeEquality(i_m1.values[10], i_m2.values[10]) &&
		FloatCalcs::relativeEquality(i_m1.values[11], i_m2.values[11]) &&

		FloatCalcs::relativeEquality(i_m1.values[12], i_m2.values[12]) &&
		FloatCalcs::relativeEquality(i_m1.values[13], i_m2.values[13]) &&
		FloatCalcs::relativeEquality(i_m1.values[14], i_m2.values[14]) &&
		FloatCalcs::relativeEquality(i_m1.values[15], i_m2.values[15]))
	{
		return false;
	}

	return true;

}

//Column Vector?
inline Vector4 operator*(const Matrix4& i_m, const Vector4& i_v)
{
	assert(!FloatCalcs::isNaN(i_v.GetX()));
	assert(!FloatCalcs::isNaN(i_v.GetY()));
	assert(!FloatCalcs::isNaN(i_v.GetZ()));
	assert(!FloatCalcs::isNaN(i_v.GetW()));

	float v_1 = i_m.values[0] * i_v.GetX() + i_m.values[1] * i_v.GetY() + i_m.values[2] * i_v.GetZ() + i_m.values[3] * i_v.GetW();
	float v_2 = i_m.values[4] * i_v.GetX() + i_m.values[5] * i_v.GetY() + i_m.values[6] * i_v.GetZ() + i_m.values[7] * i_v.GetW();
	float v_3 = i_m.values[8] * i_v.GetX() + i_m.values[9] * i_v.GetY() + i_m.values[10] * i_v.GetZ() + i_m.values[11] * i_v.GetW();
	float v_4 = i_m.values[12] * i_v.GetX() + i_m.values[13] * i_v.GetY() + i_m.values[14] * i_v.GetZ() + i_m.values[15] * i_v.GetW();
	return Vector4(v_1, v_2, v_3, v_4);
}

//Row Vector?
inline Vector4 operator*(const Vector4& i_v, const Matrix4& i_m)
{
	assert(!FloatCalcs::isNaN(i_v.GetX()));
	assert(!FloatCalcs::isNaN(i_v.GetY()));
	assert(!FloatCalcs::isNaN(i_v.GetZ()));
	assert(!FloatCalcs::isNaN(i_v.GetW()));

	float v_1 = i_m.values[0] * i_v.GetX() + i_m.values[4] * i_v.GetY() + i_m.values[8] * i_v.GetZ() + i_m.values[12] * i_v.GetW();
	float v_2 = i_m.values[1] * i_v.GetX() + i_m.values[5] * i_v.GetY() + i_m.values[9] * i_v.GetZ() + i_m.values[13] * i_v.GetW();
	float v_3 = i_m.values[2] * i_v.GetX() + i_m.values[6] * i_v.GetY() + i_m.values[10] * i_v.GetZ() + i_m.values[14] * i_v.GetW();
	float v_4 = i_m.values[3] * i_v.GetX() + i_m.values[7] * i_v.GetY() + i_m.values[11] * i_v.GetZ() + i_m.values[15] * i_v.GetW();
	return Vector4(v_1, v_2, v_3, v_4);
}

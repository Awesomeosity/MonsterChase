#pragma once
#include <array>
#include "Vector4.h"
class Matrix4
{
public:
	Matrix4();
	Matrix4(float x11, float x12, float x13, float x14,
			float x21, float x22, float x23, float x24,
			float x31, float x32, float x33, float x34,
			float x41, float x42, float x43, float x44);
	Matrix4(const Matrix4& i_matrix);
	Matrix4(const Vector4& xx1, const Vector4& xx2, const Vector4& xx3, const Vector4& xx4);
	Matrix4(Matrix4&& i_matrix) noexcept;
	Matrix4& operator=(Matrix4&& i_matrix) noexcept;

	inline Matrix4 operator=(const Matrix4& i_matrix);
	inline Matrix4 operator+=(const Matrix4& i_matrix);
	inline Matrix4 operator-=(const Matrix4& i_matrix);
	inline Matrix4 operator*=(const float i_scalar);
	inline Matrix4 operator/=(const float i_scalar);

	friend inline Matrix4 operator+(const Matrix4& i_m1, const Matrix4& i_m2);
	friend inline Matrix4 operator-(const Matrix4& i_m1, const Matrix4& i_m2);
	friend inline Matrix4 operator*(const Matrix4& i_m, const float scalar);
	friend inline Matrix4 operator*(const float scalar, const Matrix4& i_m);
	friend inline Matrix4 operator/(const Matrix4& i_m, const float scalar);
	friend inline bool operator==(const Matrix4& i_m1, const Matrix4& i_m2);
	friend inline bool operator!=(const Matrix4& i_m1, const Matrix4& i_m2);

	//Matrix multiplication
	friend inline Vector4 operator*(const Matrix4& i_m, const Vector4& i_v);
	friend inline Vector4 operator*(const Vector4& i_v, const Matrix4& i_m);

	//Static functions for generating matrices based on given values
	static Matrix4 GenerateRotationMatrix(const float angle);
	static Matrix4 GenerateScalingMatrix(const float scale_X, const float scale_Y);
	static Matrix4 GenerateTransformMatrix(const float dX, const float dY, const float dZ);
	
	//Transpose and Inversion
	void Transpose();
	Matrix4 GenerateTranspose() const;

	void Invert();
	Matrix4 GenerateInvert() const;

	//General access
	inline float operator()(unsigned int x, unsigned int y);
private:
	void swap(int index_1, int index_2);
	std::array<float, 16> values;
};

inline Matrix4 operator+(const Matrix4& i_m1, const Matrix4& i_m2);
inline Matrix4 operator-(const Matrix4& i_m1, const Matrix4& i_m2);
inline Matrix4 operator*(const Matrix4& i_m, const float scalar);
inline Matrix4 operator*(const float scalar, const Matrix4& i_m);
inline Matrix4 operator/(const Matrix4& i_m, const float scalar);
inline bool operator==(const Matrix4& i_m1, const Matrix4& i_m2);
inline bool operator!=(const Matrix4& i_m1, const Matrix4& i_m2);

//Matrix multiplication
inline Vector4 operator*(const Matrix4& i_m, const Vector4& i_v);
inline Vector4 operator*(const Vector4& i_v, const Matrix4& i_m);
#include "Matrix4-inl.h"
#pragma once
#include "Point2D.h"
class Vector4
{
public:
	Vector4();
	Vector4(float X, float Y, float Z, float W);
	Vector4(float X, float Y, float Z);
	Vector4(float X, float Y);
	Vector4(const Vector4& i_vector);
	Vector4(const Point2D& i_point, float z, float w);
	Vector4(Vector4&& i_vector) noexcept;
	Vector4(Point2D&& i_point, float z, float w) noexcept;
	Vector4& operator=(const Vector4& i_vector);
	Vector4& operator=(Vector4&& i_vector) noexcept;
	Vector4& operator=(Point2D&& i_point) noexcept;

	inline Vector4 operator+=(const Vector4& i_vector);
	inline Vector4 operator+=(const Point2D& i_point);
	inline Vector4 operator-=(const Vector4& i_vector);
	inline Vector4 operator-=(const Point2D& i_point);
	inline Vector4 operator*=(const float i_scalar);
	inline Vector4 operator/=(const float i_scalar);

	inline float GetX() const;
	inline float GetY() const;
	inline float GetZ() const;
	inline float GetW() const;

	void SetX(const float value);
	void SetY(const float value);
	void SetZ(const float value);
	void SetW(const float value);

private:
	float _X;
	float _Y;
	float _Z;
	float _W;
};

inline Vector4 operator+(const Vector4& i_v1, const Vector4& i_v2);
inline Vector4 operator-(const Vector4& i_Point2D);
inline Vector4 operator-(const Vector4& i_v1, const Vector4& i_v2);
inline Vector4 operator*(const Vector4& i_v1, const float i_scalar);
inline Vector4 operator*(const float i_scalar, const Vector4& i_v1);
inline Vector4 operator*(const Vector4& i_v1, const Vector4& i_v2);
inline Vector4 operator/(const Vector4& i_v1, const float i_scalar);
inline bool operator==(const Vector4& i_v1, const Vector4& i_v2);
inline bool operator!=(const Vector4& i_v1, const Vector4& i_v2);

#include "Vector4-inl.h"
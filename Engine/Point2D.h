#pragma once
class Point2D
{
public:
	Point2D();
	Point2D(const float i_x, const float i_y);
	Point2D(const Point2D& i_point);
	Point2D(Point2D&& i_point) noexcept;
	Point2D& operator=(Point2D&& i_point) noexcept;
	inline Point2D operator=(const Point2D& i_Point2D);
	inline Point2D operator+=(const Point2D& i_Point2D);
	inline Point2D operator-=(const Point2D& i_Point2D);
	inline Point2D operator*=(const float i_scalar);
	inline Point2D operator/=(const float i_scalar);


	inline float GetX() const;
	inline float GetY() const;
	void SetX(const float i_x);
	void SetY(const float i_y);

	void Point2D_UnitTest();
private:
	float _X;
	float _Y;
};

inline Point2D operator+(const Point2D & i_p1, const Point2D & i_p2);
inline Point2D operator-(const Point2D & i_Point2D);
inline Point2D operator-(const Point2D & i_p1, const Point2D & i_p2);
inline Point2D operator*(const Point2D& i_p1, const float i_scalar);
inline Point2D operator/(const Point2D& i_p1, const float i_scalar);
inline bool operator==(const Point2D& i_p1, const Point2D& i_p2);
inline bool operator!=(const Point2D& i_p1, const Point2D& i_p2);

#include "Point2D-inl.h"
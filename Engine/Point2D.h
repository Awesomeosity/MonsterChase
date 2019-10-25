#pragma once
class Point2D
{
public:
	Point2D(float x = 0, float y = 0);
	Point2D(const Point2D& point);
	inline Point2D operator=(const Point2D& Point2D);
	inline Point2D operator+=(const Point2D& Point2D);
	inline Point2D operator-=(const Point2D& Point2D);
	inline Point2D operator*=(const float scalar);
	inline Point2D operator/=(const float scalar);


	inline float GetX() const;
	inline float GetY() const;
	void SetX(const float x);
	void SetY(const float y);

	void Point2D_UnitTest();
private:
	float _X;
	float _Y;
};

inline Point2D operator+(const Point2D &p1, const Point2D &p2);
inline Point2D operator-(const Point2D &Point2D);
inline Point2D operator-(const Point2D &p1, const Point2D &p2);
inline Point2D operator*(const Point2D& p1, const float scalar);
inline Point2D operator/(const Point2D& p1, const float scalar);
inline bool operator==(const Point2D& p1, const Point2D& p2);
inline bool operator!=(const Point2D& p1, const Point2D& p2);

#include "Point2D-inl.h"
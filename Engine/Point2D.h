#pragma once
class Point2D
{
public:
	Point2D(float x = 0, float y = 0);
	Point2D(const Point2D& point);
	Point2D operator=(const Point2D Point2D);
	Point2D operator+=(const Point2D Point2D);
	Point2D operator-=(const Point2D Point2D);
	Point2D operator*=(float scalar);
	Point2D operator/=(float scalar);


	float GetX() const;
	float GetY() const;
	void SetX(float x);
	void SetY(float y);

	void Point2D_UnitTest();
private:
	float _X;
	float _Y;
};

Point2D operator+(const Point2D &p1, const Point2D &p2);
Point2D operator-(const Point2D &Point2D);
Point2D operator-(const Point2D &p1, const Point2D &p2);
Point2D operator*(const Point2D& p1, float scalar);
Point2D operator/(const Point2D& p1, float scalar);
bool operator==(const Point2D& p1, const Point2D& p2);
bool operator!=(const Point2D& p1, const Point2D& p2);
#pragma once
class Point2D
{
public:
	Point2D(int x = 0, int y = 0);
	Point2D(const Point2D& point);
	Point2D operator=(const Point2D Point2D);
	Point2D operator+=(const Point2D Point2D);
	int GetX() const;
	int GetY() const;
	void SetX(int x);
	void SetY(int y);
private:
	int _X;
	int _Y;
};

Point2D operator+(const Point2D &p1, const Point2D &p2);
Point2D operator-(const Point2D &p1, const Point2D &p2);
bool operator==(const Point2D& p1, const Point2D& p2);
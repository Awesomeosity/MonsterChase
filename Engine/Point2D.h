#pragma once
class Point2D
{
private:
	int _X;
	int _Y;
public:
	Point2D(int x = 0, int y = 0);
	int GetX() const;
	int GetY() const;
	void SetX(int x);
	void SetY(int y);
};

Point2D operator+(const Point2D &p1, const Point2D &p2);
Point2D operator-(const Point2D &p1, const Point2D &p2);
bool operator==(const Point2D& p1, const Point2D& p2);
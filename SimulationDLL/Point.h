#pragma once
class Point
{
public:
	Point();
	Point(double x_, double y_);
	~Point();
	double Distance(Point pt);

public:
	double x{ 0 }, y{ 0 }; // yes, these are public!
};


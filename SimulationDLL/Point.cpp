#include "Point.h"
#include <math.h>


Point::Point()
{
}

Point::Point(double x_, double y_) : x(x_), y(y_)
{
}


Point::~Point()
{
}

double Point::Distance(Point pt)
{
	double dx = x - pt.x;
	double dy = y - pt.y;
	return(sqrt((dx * dx) + (dy * dy)));
}

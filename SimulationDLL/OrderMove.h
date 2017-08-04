#pragma once

#include "Order.h"
#include "Point.h"

class OrderMove : public Order
{
public:
	OrderMove() = delete;
	OrderMove( Point pt );  // you create a new move order with the destination location always.  It can't be set after creation.
	virtual ~OrderMove();
	virtual double DistanceToTarget( Point ptCurrent );

private:
	Point ptTarget;
};


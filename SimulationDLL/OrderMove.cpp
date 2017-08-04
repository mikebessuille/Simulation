
#include "OrderMove.h"

// TODO: really should convert this into a location object (point) that includes x, y values in it.
OrderMove::OrderMove( Point pt ) : ptTarget( pt )
{
}


OrderMove::~OrderMove()
{
}


double OrderMove::DistanceToTarget(Point ptCurrent)
{
	return(ptCurrent.Distance(ptTarget));
}
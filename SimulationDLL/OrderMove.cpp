
#include "OrderMove.h"
#include "MoveComponent.h"

// TODO: really should convert this into a location object (point) that includes x, y values in it.
OrderMove::OrderMove( Point pt ) : ptTarget( pt )
{
}


OrderMove::~OrderMove()
{
}


// Returns true if the order is valid and continues to execute.  Returns false if the order is invalid or if it's complete.
bool OrderMove::Execute( GameState &gs, UnitBase *punit )
{
	if (punit == nullptr)
	{
		return(false);
	}

	shared_ptr<MoveComponent> pmc = punit->GetMoveComponent();
	if ( pmc == nullptr)
	{
		return(false);
	}

	pmc->Move(gs, ptTarget);

	// TODO: if it's close enough, return False since this order is complete.  Else return true.

	return(true);
}

double OrderMove::DistanceToTarget(Point ptCurrent)
{
	return(ptCurrent.Distance(ptTarget));
}

#include "OrderMove.h"
#include "MoveComponent.h"

OrderMove::OrderMove( Point pt ) : ptTarget( pt )
{
}


OrderMove::~OrderMove()
{
}


// Returns true if the order is valid and continues to execute.  Returns false if the order is invalid or if it's complete.
bool OrderMove::Execute( GameState &gs, UnitBase *punit, unsigned long nTick )
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
	if (pmc->AtDestination(ptTarget))
	{
		// if it's close enough, return False since this order is complete.  Else return true.
		return(false);
	}

	pmc->Move(gs, ptTarget);
	return(true);
}

double OrderMove::DistanceToTarget(Point ptCurrent)
{
	return(ptCurrent.Distance(ptTarget));
}
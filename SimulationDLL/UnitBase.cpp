#include "UnitBase.h"
#include <assert.h>


UnitBase::UnitBase()
{
	nLastUpdateTick = 0;	// TODO: Remove this...
	x = y = 0;		// TODO: probably should remain part of the base class, since all units will have a location.
	dx = dy = 0;	// TODO: Move to a "movable" class, since not all units (ex, structures) can move.
}


UnitBase::~UnitBase()
{
}


void UnitBase::Action( GameState &gs, const unsigned long nTick )
{
	// nLastUpdateTick is not needed, because we must never process more than one tick at a time for each unit,
	// because that would break exact determinism between different machines in the same game.
	// For now, use it as error checking to ensure we update every tick.
	assert(nLastUpdateTick == 0 || nTick == nLastUpdateTick + 1);
	nLastUpdateTick = nTick;
}



// TODO:  Use Composite design pattern so that the base class is an abstraction can represent a single unit, or a group of units.
// That way, other operations can treat the class the same whether it's a single tank or a group (army) of tanks.

// TODO:  Define units by composition rather than inheritance.

// TODO:  Make UnitBase virtual...
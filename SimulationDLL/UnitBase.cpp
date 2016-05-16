#include "UnitBase.h"
#include <assert.h>


UnitBase::UnitBase()
{
	nLastUpdateTick = 0;
	x = y = 0;
	dx = dy = 0;
}


UnitBase::~UnitBase()
{
}


void UnitBase::Action( GameState &gs, unsigned long nTick )
{
	// nLastUpdateTick is not needed, because we must never process more than one tick at a time for each unit,
	// because that would break exact determinism between different machines in the same game.
	// For now, use it as error checking to ensure we update every tick.
	assert(nLastUpdateTick == 0 || nTick == nLastUpdateTick + 1);
	nLastUpdateTick = nTick;
}
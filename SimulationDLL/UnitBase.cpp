#include "UnitBase.h"



UnitBase::UnitBase()
{
	nLastUpdateTick = 0;
	x = y = 0;
	dx = dy = 0;
}


UnitBase::~UnitBase()
{
}


void UnitBase::Action( unsigned long nTick )
{
	// TODO: Get rid of nLastUpdateTick; not needed, because we must never process more than one tick at a time for each unit,
	// because that would break exact determinism between different machines in the same game.
	nLastUpdateTick = nTick;
}
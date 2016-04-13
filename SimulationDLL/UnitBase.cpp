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
	// Move the unit...

	nLastUpdateTick = nTick;
}
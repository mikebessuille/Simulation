#include "UnitBase.h"



UnitBase::UnitBase()
{
	nLastUpdateTick = 0;
}


UnitBase::~UnitBase()
{
}


void UnitBase::Action( unsigned long nTick )
{
	// Move the unit...

	nLastUpdateTick = nTick;
}
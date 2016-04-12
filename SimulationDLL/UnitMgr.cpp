#include "UnitMgr.h"


/*
Details of the list should remain private to this class.  Users of the class can pass or get individual units,
but should not know the index of the unit in the list, or the implementation of that storage.
Konstantin told me to use a std::list instead of a vector...
*/


UnitMgr::UnitMgr()
{
}


UnitMgr::~UnitMgr()
{
	// C++11 functionality for iterators!
	for (auto &it : unitList)
	{
		delete it;
		// it = unitList.erase(it); // No need to erase each value if we're going to clear the entire vector!
	}
	unitList.clear();
}

void UnitMgr::AddUnit(UnitBase * pUnit)
{
	unitList.push_back(pUnit);
}


// Private method to destroy a unit at a specific index
void UnitMgr::DestroyUnit(std::list<UnitBase*>::iterator it)
{
	UnitBase *pUnit = *it;
	if( pUnit )
	{
		unitList.erase( it );
		delete pUnit;
	}
	// TODO:  else, we've passed an iterator that doesn't correctly point to a valid Unit.  Throw exception?
}


// removes the unit from this list without destroying it (for example, if you're moving this unit to another UnitMgr).
void UnitMgr::RemoveUnit(std::list<UnitBase*>::iterator it )
{
	UnitBase *pUnit = *it;
	if (pUnit)
	{
		unitList.erase( it );
	}
	// TODO:  else, we've passed an iterator that doesn't correctly point to a valid Unit.  Throw exception?
}


// Take action on each unit, called once per tick
void UnitMgr::Action(unsigned long nTick, std::chrono::milliseconds nTickSize)
{
	for (auto &it : unitList)
	{
		// Do something with each unit
		it->Action(nTick);
	}
}
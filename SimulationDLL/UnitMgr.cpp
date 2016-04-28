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
// TickSize used to determine how far to move each unit.
void UnitMgr::Action(unsigned long nTick)
{
	for (auto &it : unitList)
	{
		// Do something with each unit
		it->Action(nTick);

		// TODO:  Check to make sure we haven't spent too much time in this loop.
		// May not update all units each tick, if we run out of time.
		// Which is why each unit stores its last-updated-tick value each time it gets an action.
		// need some mechanism to evaluate which units haven't taken an action recently and do them first.
		// (Build a list of pointers to least-recently-updated units, and go through them IF the previous tick didn't
		// manage to upate all units)

		// TODO:  NO!  The above is wrong.  Never process more than one tick at a time, and always process a whole tick.
		// The system has to be deterministic between all machines running the exact same simulation.  A tick must be processed as a whole,
		// in exactly the same way (same order, same random seed, etc) in order to ensure it is identical on each machine in the network.
	}
}
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
	// C++11 functionality for iterators!  Make sure to use & for a reference, so we don't make a copy of each unit in the list
	for (auto &it : unitList)
	{
		// delete it; // this was needed when unitList was a list of UnitBase*.  Now that it's a list of shared_ptr, we just need to clear the ptrs.
		// it = unitList.erase(it); // No need to erase each value if we're going to clear the entire vector!

		// Clear the orders of the unit first; they may point to other units, and because we're using smart pointers,
		// the units may never get deleted if they're pointing at each other.
		it->ClearOrders();
	}
	unitList.clear();
}

void UnitMgr::AddUnit(shared_ptr<UnitBase> pUnit)
{
	unitList.push_back(pUnit);
}


// Private method to destroy a unit at a specific index
void UnitMgr::DestroyUnit(std::list<shared_ptr<UnitBase>>::iterator it)
{
	shared_ptr<UnitBase> pUnit = *it;
	if( pUnit )
	{
		pUnit->ClearOrders();
		unitList.erase( it );
		// delete pUnit; // No need to delete since it's a smart pointer.
	}
	// LATER: else, we've passed an iterator that doesn't correctly point to a valid Unit.  Throw exception?
	// LATER: Having to use iterators and lists is probably not very efficient.  We probably want a way to directly access
	// units, like a big array where the index is just the Unit ID (or ID of that component).
}


// removes the unit from this list without destroying it (for example, if you're moving this unit to another UnitMgr).
// This public method shouldn't take a list iterator, as that exposes the UnitMgr's implementation
// and makes it difficult to change in the future (for example, to store an array of units).
void UnitMgr::RemoveUnit(std::list<shared_ptr<UnitBase>>::iterator it )
{
	shared_ptr<UnitBase> pUnit = *it;
	if (pUnit)
	{
		unitList.erase( it );
	}
	// LATER:  else, we've passed an iterator that doesn't correctly point to a valid Unit.  Throw exception?
}


// Take action on each unit, called once per tick.  Must be called once per tick, in order to keep this deterministic
// between all the machines in the game so that they all run the exact same simulation.
// Always process an entire tick at once, for all units.  Must be in the exact same order on each machine in the game.
// Never try to process multiple ticks at once!
void UnitMgr::Update( GameState &gs, const unsigned long nTick)
{
	for (auto &it : unitList)
	{
		// Do something with each unit
		it->Update(gs, nTick);

		// TODO:  How do we get the ticksize into each unit?  It's owned by the TickControl object...  Should be a static set
		// into UnitBase?
		// TickSize used to determine how far to move each unit.
		// Set the UnitBase "FrameSize" static from TickControl?  Or from Simulation???   Set it into new GameState??
	}
}


void UnitMgr::Render(GameState &gs, Map &map)
{
	for (auto &it : unitList)
	{
		// Render each unit

		it->Render( gs, map );
	}
}

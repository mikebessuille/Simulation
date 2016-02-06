#include "UnitMgr.h"


/*
Details of the list should remain private to this class.  Users of the class can pass or get individual units,
but should not know the index of the unit in the list, or the implementation of that storage.
*/


UnitMgr::UnitMgr()
{
}


UnitMgr::~UnitMgr()
{
	/* Older iterator format...
	for (std::vector<Unit*>::iterator it = unitList.begin(); it != unitList.end(); ++it)
	{
		// std::cout << *it; ...
	}
	*/

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
void UnitMgr::DestroyUnit(int id, UnitBase * pUnit)
{
	if (pUnit == unitList.at(id))
	{
		unitList.erase( unitList.begin() + id);
		delete pUnit;
	}
	// TODO:  else, we've passed an index that doesn't correctly refer to the pUnit param.  Throw exception?
}


// removes the unit from this list without destroying it (for example, if you're moving this unit to another UnitMgr).
void UnitMgr::RemoveUnit( int id, UnitBase * pUnit)
{
}

/* STD: Vector iterator:  Something like this:
for (auto &unit : UM.unitList)
{
	unit->...();
}
*/
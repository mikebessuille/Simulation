#include "UnitMgr.h"



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

#pragma once

#include "UnitBase.h"
#include <vector>
#include <iostream>


// using namespace std;

// Forward declare the unit test class so it can be a friend of this class, despite being in a different namespace
// and a different project
namespace UnitTestProject {
	class UnitMgrTest;
}

class UnitMgr
{
	friend class UnitTestProject::UnitMgrTest; // so that the tests can call private methods.

// Class Variables
private:
	std::vector<UnitBase*> unitList;

// Class Methods
public:
	UnitMgr();
	~UnitMgr();
	void Action();
	
private:
	int NumUnits() { return unitList.size(); }
	void AddUnit(UnitBase *pUnit);
	void DestroyUnit(int id, UnitBase *pUnit);
	void RemoveUnit(int id, UnitBase *pUnit);
};


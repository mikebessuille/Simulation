#pragma once

#include "UnitBase.h"
#include <list>
#include <iostream>
#include <chrono>


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
	std::list<UnitBase*> unitList;

// Class Methods
public:
	UnitMgr();
	~UnitMgr();
	void Action( unsigned long nTick, std::chrono::milliseconds nTickSize );
	
private:
	int NumUnits() { return unitList.size(); }
	void AddUnit(UnitBase *pUnit);
	void DestroyUnit( std::list<UnitBase*>::iterator it);
	void RemoveUnit(std::list<UnitBase*>::iterator it);
};


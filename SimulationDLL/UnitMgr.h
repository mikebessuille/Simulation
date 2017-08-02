#pragma once

#include "GameState.h"
#include "UnitBase.h"
#include "Map.h"
#include <list>
#include <iostream>
#include <chrono>
#include <mutex>


// using namespace std;

// Forward declare the unit test class so it can be a friend of this class, despite being in a different namespace
// and a different project
// This is no longer needed, now that most of this class' methods are public.
namespace UnitTestProject {
	class UnitMgrTest;
	class UnitAndComponentTest;
}

class GameState;
class UnitBase;

class UnitMgr
{
	friend class UnitTestProject::UnitMgrTest; // so that the tests can call private methods.
	friend class UnitTestProject::UnitAndComponentTest;

// Class Variables
private:
	std::list<UnitBase*> unitList;
	mutex um_mtx; // for controlling multi-thread access to this UnitManager instance

// Class Methods
public:
	UnitMgr();
	~UnitMgr();
	void Update( GameState &gs, const unsigned long nTick );
	void Render( GameState &gs, Map &map );
	mutex & GetMutex() { return( std::ref( um_mtx )); };
	
public:	// not sure why these methods were private at one point...
	int NumUnits() { return unitList.size(); }
	void AddUnit(UnitBase *pUnit);
	void DestroyUnit( std::list<UnitBase*>::iterator it);
	void RemoveUnit(std::list<UnitBase*>::iterator it);
};


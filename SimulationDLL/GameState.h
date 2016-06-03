#pragma once

#include <list>
#include <chrono>
#include "UnitMgr.h"


// The GameState class contains all the data needed to run a simulation, or to render a particular frame.
// Need to make access to GameState threadsafe so that Render() and Simulation Update() calls don't have concurrency problems.

// Forward declare the unit test class so it can be a friend of this class, despite being in a different namespace
// and a different project
namespace UnitTestProject {
	class ThreadTest;
}

// Forward declare UnitMgr
class UnitMgr;

using namespace std;

class GameState
{
	friend class UnitTestProject::ThreadTest; // so that the tests can call private methods.

// Member Variables... really, these are public???
public:
	std::list<UnitMgr *> UMList;		// List of UnitMgr's, each with its own list of units (for each player).
	chrono::milliseconds nTickSize;		// TickSize used to determine how far to move each unit.

// Class Methods
public:
	GameState();
	~GameState();
};


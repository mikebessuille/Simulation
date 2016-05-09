#pragma once

#include <list>
#include "UnitMgr.h"


// The GameState class contains all the data needed to run a simulation, or to render a particular frame.
// Need to make access to GameState threadsafe so that Render() and Simulation Update() calls don't have concurrency problems.

// Forward declare the unit test class so it can be a friend of this class, despite being in a different namespace
// and a different project
namespace UnitTestProject {
	class ThreadTest;
}


class GameState
{
	friend class UnitTestProject::ThreadTest; // so that the tests can call private methods.

// Member Variables
public:
	std::list<UnitMgr *> UMList;

// Class Methods
public:
	GameState();
	~GameState();
};


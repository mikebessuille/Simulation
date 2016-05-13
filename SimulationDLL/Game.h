#pragma once
#include "Simulation.h"
#include "GameState.h"
#include "Player.h"
#include <list>

// Game class to hold the simulation, players, etc.


// Forward declare the unit test class so it can be a friend of this class, despite being in a different namespace
// and a different project
namespace UnitTestProject {
	class ThreadTest;
}


class Game
{
	friend class UnitTestProject::ThreadTest; // so that the tests can call private methods.

// Member Variables
private:
	Simulation sim;
	GameState gs;
	bool bInitialized = false;

public:
	std::list<Player> playerList;

// Class Methods
public:
	Game();
	~Game();

	bool InitializeGame();
	void Start();
	void Stop();

	GameState & GetGameState();
};


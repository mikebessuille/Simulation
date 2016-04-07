#pragma once
#include "Simulation.h"
#include "Player.h"
#include <list>

// Game class to hold the simulation, players, etc.

class Game
{
// Member Variables
public:
	Simulation sim;
	std::list<Player> playerList;

// Class Methods
public:
	Game();
	~Game();

};


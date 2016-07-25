
#include "SimDLL.h"
#include "Game.h"
#include "Simulation.h"

bool DLLClass::RunSimulation()
{
	// Old, replaced by Game object
	//Simulation sim;
	//sim.Start();

	Game game;

	game.InitializeGame();
	game.Start();

	return(true);
}




#include "SimDLL.h"
#include "Game.h"
#include "Simulation.h"

bool DLLClass::RunSimulation()
{
	Game game;

	game.InitializeGame();
	game.Start();

	return(true);
}



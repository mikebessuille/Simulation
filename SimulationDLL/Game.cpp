#include "Game.h"
#include <assert.h>

// Game class to hold the simulation, players, etc.

Game::Game() : 
	sim(this),
	renderer(this)
{

}

Game::~Game()
{
}

bool Game::InitializeGame()
{
	// Initialize the Simulation

	// Initialize the GameState and its pointers to each player's Unit Manager
	for (auto player : playerList) // this was (Player &player, ... ) when playerList was a list of Players instead of pointers to players.
	{
		gs.UMList.push_back(&(player->UM));
	}

	bInitialized = true;
	return(bInitialized);
}

void Game::Start()
{
	// assert(bInitialized); // causes INVARIANT_CONDITION.UNREACH on next line
	if (bInitialized == true )
	{
		sim.Start();
		renderer.Start();
	}
}

void Game::Stop()
{
	//if (bInitialized)
	//{
		sim.Stop();
		renderer.Stop();
	//}
}

GameState & Game::GetGameState()
{
	return gs;  // This returns a reference to the gamestate.
}
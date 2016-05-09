#include "Game.h"
#include <assert.h>

// Game class to hold the simulation, players, etc.

Game::Game() : sim(this)
{

}

Game::~Game()
{
}

bool Game::InitializeGame()
{
	// Initialize the Simulation

	// Initialize the GameState and its pointers to each player's Unit Manager
	for (auto player : playerList)
	{
		gs.UMList.push_back(&(player.UM));
	}

	bInitialized = true;
	return(bInitialized);
}

void Game::Start()
{
	assert(bInitialized);
	if (bInitialized == true )
	{
		sim.Start();
	}
}

void Game::Stop()
{
	if (bInitialized)
	{
		sim.Stop();
	}
}
#include "Game.h"

// Game class to hold the simulation, players, etc.

Game::Game() : sim(this)
{
	// Todo:  move this to a unit (integration) test...
	playerList.push_back(Player("Mike"));
	playerList.push_back(Player("Bob"));
	playerList.push_back(Player("Sally"));

	// TODO: initialize each player's Unit Manager

}


Game::~Game()
{
}

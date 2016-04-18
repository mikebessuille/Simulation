// SimulationConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

// #include "SimDLL.h"
#include "Simulation.h"
#include "Game.h"
#include "Player.h"

using namespace std;


void CreateSomeUsers( Game &g )
{
	g.playerList.push_back(Player("Mike"));
	g.playerList.push_back(Player("Bob"));
	g.playerList.push_back(Player("Sally"));
}


int main()
{
	std::cout << "Simulation Console Running.  Hit Enter to start Simulation..." << endl;
	// std::cin.ignore(); // Accepts user input.
	std::cin.get(); // gets any user input (requires user to hit enter as well)

	/*
	DLLClass simDLL;
	simDLL.RunSimulation();
	*/

	Game game;

	// TODO:  Move all this to a new Unit Test!!!
	CreateSomeUsers(game);

	cout << "Players:" << endl;
	for (auto pl : game.playerList)
	{
		cout << pl.Name << endl;
	}
	cout << endl;

	cout << "Simulation Looping: Hit Enter to stop..." << endl;
	game.sim.Start();
	cin.get(); // Waits for user input (enter).  Then stops the sim.
	game.sim.Stop();


	// Test to see if we can restart the simulation after it's been stopped.
	cout << "Hit Enter to restart..." << endl;
	std::cin.get();
	game.sim.Start();
	cin.get(); // Waits for user input (enter).  Then stops the sim.
	game.sim.Stop();

    return 0;
}


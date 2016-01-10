// SimulationConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "SimDLL.h"
#include "Simulation.h"

int main()
{
	std::cout << "Simulation Console Running\n";
	// std::cin.ignore(); // Accepts user input but doesn't ever close.
	std::cin.get(); // gets any user input (requires user to hit enter as well)

	/*
	DLLClass simDLL;
	simDLL.RunSimulation();
	*/

	Simulation sim;
	sim.Start();

	std::cin.get(); // Waits for user input (enter).  Then stops the sim.
	sim.Stop();

    return 0;
}


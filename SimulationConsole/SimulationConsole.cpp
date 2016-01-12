// SimulationConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

// #include "SimDLL.h"
#include "Simulation.h"

using namespace std;

int main()
{
	std::cout << "Simulation Console Running.  Hit Enter to start Simulation..." << endl;
	// std::cin.ignore(); // Accepts user input.
	std::cin.get(); // gets any user input (requires user to hit enter as well)

	/*
	DLLClass simDLL;
	simDLL.RunSimulation();
	*/

	cout << "Simulation Looping: Hit Enter to stop..." << endl;

	Simulation sim;
	sim.Start();

	cin.get(); // Waits for user input (enter).  Then stops the sim.
	sim.Stop();

    return 0;
}


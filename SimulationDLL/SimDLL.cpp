
#include "SimDLL.h"
#include "Simulation.h"

bool DLLClass::RunSimulation()
{
	Simulation sim;

	sim.Start();

	return(true);
}



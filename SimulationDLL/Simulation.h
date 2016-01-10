#pragma once

#include <iostream>
#include <thread>
#include "SimDLL.h"

#define MAX_TICK 5000000

class SIM_API Simulation
{
// Private Variables
private:
	bool bRunning;
	std::thread SimThread; 

public:
	Simulation();
	~Simulation();

	void Start();
	void Stop();
	bool IsRunning() { return(bRunning); }
	
// Private Methods
private:	
	void Loop();
};
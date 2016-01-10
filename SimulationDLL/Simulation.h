#pragma once

#include <iostream>
#include <thread>
#include "SimDLL.h"

#define MAX_TICK 5000000

class SIM_API Simulation
{
public:
	Simulation();
	~Simulation();

	void Start();
	void Stop();

// Private Variables
private:
	bool bRunning;
	std::thread SimThread;
	
// Private Methods
private:	
	void Loop();
};
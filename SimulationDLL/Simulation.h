#pragma once

#include <iostream>
#include <thread>
#include "SimDLL.h"
#include "TickControl.h"

#define MAX_TICK 5000000

using namespace std;

class SIM_API Simulation
{
// Private Variables
private:
	bool bRunning;
	thread SimThread; 

public:
	Simulation();
	~Simulation();

	void Start();
	void Stop();
	bool IsRunning() { return(bRunning); }
	
// Private Methods
private:	
	void Loop();
	TickControl ticker;
};
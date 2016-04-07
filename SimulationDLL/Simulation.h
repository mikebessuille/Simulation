#pragma once

#include <iostream>
#include <thread>
#include "SimDLL.h"
#include "TickControl.h"
#include <assert.h>

#define MAX_TICK 5000000

using namespace std;

class Game; // forward declare

class SIM_API Simulation
{
// Private Variables
private:
	bool bRunning;
	thread *pSimThread;		// Keep this a pointer and instantiate in constructor, so that I avoid warnings
							// about exporting a class with STL class
	TickControl *pTicker;	// Needs to be a pointer in order to avoid warnings about STL classes being exported.
	Game *pGame;			// parent!

public:
	Simulation( Game *parent );
	~Simulation();

	void Start();
	void Stop();
	bool IsRunning() { return(bRunning); }
	
// Private Methods
private:	
	void Loop();
	
	Simulation& operator=(const Simulation&) { return *this; } // Declare a private assignment operator to avoid KW CL.FFM.ASSIGN warning about multiple freeing of memory if an object was copied.
	Simulation(const Simulation& src) { /* do not create copies */ } // Declared private to avoid KW CL.FFM.COPY
};
#include "Simulation.h"
#include <thread>
// #include <chrono>


// Initialize the simulation.
Simulation::Simulation()
{
	bRunning = false;
	// pSimThread = new thread();
	pSimThread = NULL;
	pTicker = new TickControl;

	// TODO: put Simulation initialization code here?  (Load UnitMgr objects, players, ...)
}


// Clean up the simulation
Simulation::~Simulation()
{
	if (bRunning)
	{
		// some kind of error happened because the simulation object is being deleted while
		// the simluation is still running!
		cout << "Failed to Stop simulation before killing app\n";
	}
	if (pSimThread)
	{
		if (pSimThread->joinable())
			pSimThread->join();  // main thread waits for SimThread to complete

		delete pSimThread;
		pSimThread = NULL;
	}

	delete pTicker; 
	pTicker = NULL;
}

// Starts the simulation loop.  May start the simulation multiple times (after pause)
void Simulation::Start()
{
	cout << "Simulation Start\n";
	bRunning = true;
	assert(!pSimThread);
	pSimThread = new thread(&Simulation::Loop, this);
}

// Stops the simulation; could just be paused.
void Simulation::Stop()
{
	bRunning = false;

	// Join the thread to the main thread so main waits for the thread to finish.
	// Setting the bRunning flag above should accomplish the same thing; the thread should immediately exit
	// (after it finishes processing the current tick and checks bRunning again).
	if (pSimThread)
	{
		if (pSimThread->joinable())
			pSimThread->join();  // main thread waits for SimThread to complete

		delete pSimThread;
		pSimThread = NULL;
	}

	cout << "Loop Completed" << endl;
}


// The main Simulation loop, which executes on a separate thread.
void Simulation::Loop()
{
	unsigned long nTick = pTicker->GetCurrentTick();
	pTicker->Start();

	while (bRunning && nTick < MAX_TICK)
	{
		cout << "\b\b\b\b\b\b\b\b\b\b\b" << flush;
		cout << "Tick: " << nTick << flush;

		// TODO:  Put the per-tick work here

		this_thread::sleep_until(pTicker->NextTickTime());
		nTick = pTicker->Next();
	}

	cout << endl;
}
#include "Simulation.h"
#include <thread>
#include <chrono>


// Initialize the simulation.
Simulation::Simulation()
{
	bRunning = false;
	// pSimThread = new thread();
	pSimThread = NULL;
	pTicker = new TickControl;
}


// Clean up the simulation
Simulation::~Simulation()
{
	if (bRunning)
	{
		// Todo:  some kind of error happened because the simulation object is being deleted while
		// the simluation is still running!
	}
	if (pSimThread)
	{
		if (pSimThread->joinable())
			pSimThread->join();  // main thread waits for SimThread to complete

		// TODO:  Why does klocwork tell me this is double-freeing the thread??
		// delete pSimThread;
		pSimThread = NULL;
	}

	delete pTicker; 
	// pTicker = NULL;
}

// Starts the simulation loop.  May start the simulation multiple times (after pause)
void Simulation::Start()
{
	cout << "Simulation Start\n";
	bRunning = true;
	pSimThread = new thread(&Simulation::Loop, this);
}

// Stops the simulation; could just be paused.
void Simulation::Stop()
{
	bRunning = false;
	// TODO: actually stop the thread! ??
	// TODO: Then delete the thread

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

		//TODO:  This clearly isn't ever causing the current thread to sleep...
		// this_thread::sleep_until( pTicker->NextTickTime() + chrono::seconds(500));
		chrono::steady_clock::time_point sleep_until_time = pTicker->NextTickTime() + chrono::seconds(500);
		this_thread::sleep_until( sleep_until_time );


		//this_thread::sleep_until(ticker.NextTickTime());
		nTick = pTicker->Next();
	}

	cout << endl;
}

/* Happy Face annimation: (From Henry)
std::cout << "\b\b\b:)" << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(100));
std::cout << "\b\b'_'" << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(100));
std::cout << "\b\b\b(:" << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(100));
std::cout << "\b\b.-." << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(100));
*/
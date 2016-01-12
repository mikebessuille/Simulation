#include "Simulation.h"
#include <thread>
#include <chrono>


// Initialize the simulation.
Simulation::Simulation()
{
	bRunning = false;
}


// Clean up the simulation
Simulation::~Simulation()
{
	if (bRunning)
	{
		// Todo:  some kind of error happened because the simulation object is being deleted while
		// the simluation is still running!
	}
	if (SimThread.joinable())
		SimThread.join();  // main thread waits for SimThread to complete
}

// Starts the simulation loop.  May start the simulation multiple times (after pause)
void Simulation::Start()
{
	cout << "Simulation Start\n";
	bRunning = true;
	SimThread = thread(&Simulation::Loop, this);
}

// Stops the simulation; could just be paused.
void Simulation::Stop()
{
	bRunning = false;
	// TODO: actually stop the thread! ??

	cout << "Loop Completed" << endl;
}


// The main Simulation loop, which executes on a separate thread.
void Simulation::Loop()
{
	unsigned long nTick = ticker.GetCurrentTick();
	ticker.Start();

	while (bRunning && nTick < MAX_TICK)
	{
		cout << "\b\b\b\b\b\b\b\b\b\b\b" << flush;
		cout << "Tick: " << nTick << flush;

		//TODO:  This clearly isn't ever causing the current thread to sleep...
		this_thread::sleep_until( ticker.NextTickTime() + chrono::seconds(500));

		//this_thread::sleep_until(ticker.NextTickTime());
		nTick = ticker.Next();
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
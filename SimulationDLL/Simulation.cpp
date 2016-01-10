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
		SimThread.join();
}

// Starts the simulation loop.  May start the simulation multiple times (after pause)
void Simulation::Start()
{
	std::cout << "Simulation Start\n";
	bRunning = true;
	SimThread = std::thread(&Simulation::Loop, this);
}

// Stops the simulation; could just be paused.
void Simulation::Stop()
{
	bRunning = false;
	// TODO: actually stop the thread!

	std::cout << "Loop Completed\n";
}

void Simulation::Loop()
{
	int nTick = 0;
	
	std::cout << "Simulation Looping: Hit Enter to stop\n";

	while (bRunning && nTick < MAX_TICK)
	{
		std::cout << "\b\b\b\b\b\b\b\b\b\b\b" << std::flush;
		std::cout << "Tick: " << nTick << std::flush;
		nTick++;
	}

	std::cout << "\n";
}

/* Happy Face annimation:
std::cout << "\b\b\b:)" << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(100));
std::cout << "\b\b'_'" << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(100));
std::cout << "\b\b\b(:" << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(100));
std::cout << "\b\b.-." << std::flush;
std::this_thread::sleep_for(std::chrono::milliseconds(100));
*/
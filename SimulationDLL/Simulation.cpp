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

		//Test code - this wasn't working with steady_clock but works with system_clock.  Bug in STL.
		// See https://www.reddit.com/r/cpp_questions/comments/3o71ic/sleep_until_not_working_with_a_time_pointsteady/
		//chrono::system_clock::time_point cur_time = chrono::system_clock::now();
		//chrono::system_clock::time_point sleep_until_time = pTicker->NextTickTime() + chrono::seconds(500);
		// this_thread::sleep_until( sleep_until_time );


		this_thread::sleep_until(pTicker->NextTickTime());
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
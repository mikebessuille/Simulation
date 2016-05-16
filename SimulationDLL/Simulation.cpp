#include "Simulation.h"
#include "Game.h"
#include "UnitMgr.h"
#include <thread>
#include <assert.h>

mutex Simulation::simLock;

// Simulation class that owns the game state.  It does NOT have anything to do with Rendering, User Input, or Networking.

// Initialize the simulation.
Simulation::Simulation( Game *parent )
{
	bRunning = false;
	// pSimThread = new thread();
	pSimThread = NULL;
	pTicker = new TickControl;
	pGame = parent;
	assert( pGame );

	// Put Simulation initialization code here?  (Load UnitMgr objects, players, ...)

	// TODO: need to use simLock mutex to lock access to Simulation data that may be accessed by multiple threads.
	// Including Ticker?
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
	assert(bRunning == false);
	if (!bRunning )
	{
		cout << "Simulation Start\n";
		bRunning = true;

		GameState & gs = pGame->GetGameState();
		gs.nTickSize = pTicker->GetTickSize();

		assert(!pSimThread);
		pSimThread = new thread(&Simulation::Loop, this);
	}
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

		// Per-tick work:
		Update( nTick );
				
		if (pTicker->Late())
		{
			// TODO:  We spent more time processing that tick than the ticksize; if so, we are falling behind and need
			// to inform the other computers in the simulation?  Or we need to try to catch up somehow on this machine...
			cout << endl << "LATE!!  Took too long to process a tick." << endl;
		}
		else
		{
			this_thread::sleep_until(pTicker->NextTickTime());
		}
		
		// process the next tick
		nTick = pTicker->Next();
	}

	cout << endl;
}


// Perform a single update on the gamestate, across all players and all units.
void Simulation::Update( unsigned long nTick )
{
	GameState & gs = pGame->GetGameState();
	for (auto player : pGame->playerList)
	{
		player.UM.Action( gs, nTick);
	}
}
#include "TickControl.h"

const chrono::milliseconds TickControl::DefaultSimulationFrame = chrono::milliseconds(200);

// This class controls the simulation frame rate
TickControl::TickControl()
{
	nCurrentTick = 0;
	nTickSize = DefaultSimulationFrame;
	nCurrentTickTime = chrono::system_clock::now();
	bRunning = false;
}

TickControl::~TickControl()
{
}


void TickControl::Start()
{
	// starts ticking
	nCurrentTickTime = chrono::system_clock::now();
	bRunning = true;
}


void TickControl::Stop()
{
	// nCurrentTickTime = chrono::system_clock::now();
	bRunning = false;
}


// Returns the size of each simulation frame, in MS
chrono::milliseconds TickControl::GetTickSize()
{
	return( nTickSize );
}

unsigned long TickControl::GetCurrentTick()
{
	return(nCurrentTick);
}


chrono::system_clock::time_point TickControl::NextTickTime()
{
	if (bRunning)
		return(nCurrentTickTime + nTickSize);
	else
		return( nCurrentTickTime );
}


// Increments the tick and returns the new tick number.
unsigned long TickControl::Next()
{
	if (bRunning)
	{
		nCurrentTick++;
		nCurrentTickTime = chrono::system_clock::now();
	}
	return(nCurrentTick);
}

// Returns true if we are past the time that we should have started the next tick.
bool TickControl::Late()
{
	if (chrono::system_clock::now() > (nCurrentTickTime + nTickSize))
		return true;
	else
		return false;
}
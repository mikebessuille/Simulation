#include "TickControl.h"

// This class controls the simulation frame rate
TickControl::TickControl()
{
	nCurrentTick = 0;
	nTickSize = chrono::milliseconds( DEFAULT_SIMULATION_FRAME );
	nCurrentTickTime = chrono::system_clock::now();
}

TickControl::~TickControl()
{
}


void TickControl::Start()
{
	// starts ticking
	nCurrentTickTime = chrono::system_clock::now();
}


void TickControl::Stop()
{
	// nCurrentTickTime = chrono::system_clock::now();
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
	return(nCurrentTickTime + nTickSize );
}


// Increments the tick and returns the new tick number.
unsigned long TickControl::Next()
{
	nCurrentTick++;
	nCurrentTickTime = chrono::system_clock::now();
	return( nCurrentTick );
}

/*
std::chrono::time_point<std::chrono::system_clock> start, end;
start = std::chrono::system_clock::now();
std::cout << "f(42) = " << fibonacci(42) << '\n';
end = std::chrono::system_clock::now();

std::chrono::duration<double> elapsed_seconds = end-start;
std::time_t end_time = std::chrono::system_clock::to_time_t(end);

std::cout << "finished computation at " << std::ctime(&end_time)
<< "elapsed time: " << elapsed_seconds.count() << "s\n";
*/


/*
#include <chrono>
#include <iostream>

int main()
{
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;
auto t0 = Time::now();
auto t1 = Time::now();
fsec fs = t1 - t0;
ms d = std::chrono::duration_cast<ms>(fs);
std::cout << fs.count() << "s\n";
std::cout << d.count() << "ms\n";
}
*/
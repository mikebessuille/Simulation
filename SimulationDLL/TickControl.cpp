#include "TickControl.h"

// This class controls the simulation frame rate
TickControl::TickControl()
{
	nTick = 0;
	nTickSize = std::chrono::milliseconds( DEFAULT_SIMULATION_FRAME );
	nTickTime = 0;
}


void TickControl::Start()
{
	// starts ticking
	nTickTime = std::chrono::system_clock::now();
}


void TickControl::Stop()
{
	nTickTime = 0;
}

// TODO:  Need some way of incrementing the tick (should be a call from the thread loop)


// Returns the size of each simulation frame, in MS
std::chrono::duration<double> TickControl::GetTickSize()
{
	return( nTickSize );
}


std::chrono::time_point<std::chrono::system_clock> TickControl::NextTickTime()
{
	return(nTickTime + nTickSize)
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
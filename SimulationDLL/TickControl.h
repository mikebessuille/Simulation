#pragma once
#include <chrono>

#define DEFAULT_SIMULATION_FRAME 200	// ms per tick

using namespace std;

class TickControl sealed
{
public:
	TickControl();
	void Start();
	void Stop();
	chrono::milliseconds GetTickSize();
	chrono::steady_clock::time_point NextTickTime();
	unsigned long GetCurrentTick();
	unsigned long Next();

private:
	unsigned long nCurrentTick;		// The current tick number
	chrono::steady_clock::time_point nCurrentTickTime;  // The starting time of the current tick
	chrono::milliseconds nTickSize;	// The size (in MS) of each tick
};


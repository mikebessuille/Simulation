#pragma once
#include <chrono>

#define DEFAULT_SIMULATION_FRAME 200	// ms per tick

class TickControl sealed
{
public:
	TickControl();
	void Start();
	void Stop();
	std::chrono::duration<double> GetTickSize();
	std::chrono::time_point<std::chrono::system_clock> NextTickTime();

private:
	unsigned long nTick;		// The current tick number
	std::chrono::time_point<std::chrono::system_clock> nTickTime;	// The starting time of the current tick
	std::chrono::duration<double> nTickSize;	// The size (in MS) of each tick
};


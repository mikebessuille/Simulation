#pragma once
#include <chrono>

#define DEFAULT_SIMULATION_FRAME 200	// ms per tick

using namespace std;

class TickControl sealed
{
public:
	TickControl();
	~TickControl();
	void Start();
	void Stop();
	chrono::milliseconds GetTickSize();
	// Switching from steady_clock to system_clock to avoid an STL bug:  https://www.reddit.com/r/cpp_questions/comments/3o71ic/sleep_until_not_working_with_a_time_pointsteady/
	// chrono::steady_clock::time_point NextTickTime();
	chrono::system_clock::time_point NextTickTime();
	unsigned long GetCurrentTick();
	unsigned long Next();

private:
	unsigned long nCurrentTick;		// The current tick number
	// chrono::steady_clock::time_point nCurrentTickTime;  // The starting time of the current tick
	chrono::system_clock::time_point nCurrentTickTime;  // The starting time of the current tick
	chrono::milliseconds nTickSize;	// The size (in MS) of each tick
};


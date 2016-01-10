#include "TickControl.h"

// This class controls the simulation frame rate

TickControl::TickControl()
{
}

// Returns the size of each simulation frame, in MS
int TickControl::GetTickSize()
{
	return( DEFAULT_SIMULATION_FRAME );
}

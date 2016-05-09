#pragma once

class UnitBase
{
public:
	UnitBase();
	virtual ~UnitBase();
	void Action( unsigned long nTick );

// Member Variables
private:
	unsigned long nLastUpdateTick;

public:
	double x, y;	// current location; should change this to some kind of "point" structure/object
	double dx, dy;	// current velocity

	//TODO:  Need destination location (or could be a list of locations to move in succession; could be a list of patrol points)
	//TODO:  Need a pointer (or identifier) of an enemy target
	//TODO:	 Current damage amount
	//TODO:  Pointer to the current map tile
	//TODO:  Something to identify it's current orders (Move, defend, attack, patrol...)

// Statics
public:
	static unsigned long FrameSize; // milliseconds per tick.   This is a terrible design as this breaks encapsulation.
									// This information really should not be owned by this class!
};


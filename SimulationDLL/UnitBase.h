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

	//TODO:  Need destination location
	//TODO:  Need a pointer (or identifier) of an enemy target

// Statics
public:
	static unsigned long FrameSize; // milliseconds per tick
};


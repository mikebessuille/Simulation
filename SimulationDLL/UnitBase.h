#pragma once

#include "GameState.h"

class GameState;

class UnitBase
{
public:
	UnitBase();
	virtual ~UnitBase();
	void Action( GameState &gs, unsigned long nTick );

// Member Variables
private:
	unsigned long nLastUpdateTick;

public:
	double x, y;	// current location; TODO: should change this to some kind of "point" structure/object
	double dx, dy;	// current velocity

	//TODO:  Need destination location (or could be a list of locations to move in succession; could be a list of patrol points)
	//TODO:  Need a pointer (or identifier) of an enemy target.  (What if it's target is an area?)  // NOTE! Target may be destroyed (pointer may be invalid?)
	//TODO:	 Current damage / health amount
	//TODO:  Pointer to the current map tile
	//TODO:  Something to identify it's current orders (Move, defend, attack, patrol...)  Maybe an Order class with subclasses for each
	// type of order?

	// TODO: Unit Class should be constructed mostly from composition rather than inheritance!
};


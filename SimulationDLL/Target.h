#pragma once

// A target can be a unit, a location, etc.
// TODO:  Not sure I want this class.  I don't want to have to create / manage / destroy target objects every time a unit is firing at another unit

class Target
{
public:
	Target();
	virtual ~Target();
	virtual double DistanceToTarget() = 0;
};


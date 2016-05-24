#pragma once
#include "UnitComponent.h"
#include "GameState.h"

// Interface for movement components.  Ground, Air, Water all implement this interface.
class MoveComponent :  public UnitComponent
{
public:
	MoveComponent( double maxSpeed ) : m_speed(maxSpeed) {}
	virtual ~MoveComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0;


protected:
	double m_speed;	// max speed
	//TODO: Target location
	// (or could be a list of locations to move in succession; could be a list of patrol points)
	// Could be a target unit, in which case it would constantly update its path to try to intercept the target
};


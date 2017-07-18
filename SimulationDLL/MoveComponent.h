#pragma once
#include "UnitComponent.h"

class UnitComponent;
class GameState;
class Map;

// Interface for movement components.  Ground, Air, Water all implement this interface.
class MoveComponent :  public UnitComponent
{
public:
	MoveComponent( double maxSpeed ) : m_speed(maxSpeed) {}
	virtual ~MoveComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0; // keep this here to make this an interface class
	virtual void Render(GameState &gs, Map &map ) = 0;

protected:
	double m_speed;	// max speed
	//TODO: Target location
	// (or could be a list of locations to move in succession; could be a list of patrol points)
	// Could be a target unit, in which case it would constantly update its path to try to intercept the target
};


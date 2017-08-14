#pragma once
#include "UnitComponent.h"
#include "Point.h"

class UnitComponent;
class GameState;
class Map;

// Interface for movement components.  Ground, Air, Water all implement this interface.
// This class knows how to move, but not where to move (that's encompassed in a move "order")
class MoveComponent :  public UnitComponent
{
public:
	MoveComponent( double maxSpeed ) : m_speed(maxSpeed) {}
	virtual ~MoveComponent() {}
	virtual void Update(GameState &gs, unsigned long nTick) = 0; // keep this here to make this an interface class
	virtual void Render(GameState &gs, Map &map ) = 0;
	virtual void Move(GameState &gs, Point ptDest ) = 0;
protected:
	double m_speed;	// max speed
};


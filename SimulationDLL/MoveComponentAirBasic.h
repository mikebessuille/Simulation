#pragma once
#include "MoveComponent.h"
#include "Point.h"

class MoveComponentAirBasic :
	public MoveComponent
{
public:
	MoveComponentAirBasic(double maxSpeed, double dx_, double dy_);
	virtual ~MoveComponentAirBasic();
	virtual void Update(GameState &gs, unsigned long nTick);
	virtual void Render(GameState &gs, Map &map);
	virtual void Move(GameState &gs, Point ptDest);

// TODO: Put this into a base class, if all classes need it?
protected:
	double dx, dy;	// current velocity
};
#pragma once
#include "MoveComponent.h"
#include "Point.h" 

class MoveComponentGroundBasic :
	public MoveComponent
{
public:
	MoveComponentGroundBasic(double maxSpeed, double dx_, double dy_);
	virtual ~MoveComponentGroundBasic();
	virtual void Update(GameState &gs, unsigned long nTick);
	virtual void Move(GameState &gs, Point ptDest );
	virtual void Render(GameState &gs, Map &map);
	void SetSpeed(double dx_, double dy_); // non-virtual so cannot override

protected:
	double dx, dy;	// current velocity
};